#include "stdafx.h"
#include "SteeringBehaviors.h"

SteeringBehaviors::SteeringBehaviors(Vehicle * agent)
{
	//stuff for the wander behavior
	double theta = RandFloat() * TwoPi;

	//create a vector to a target position on the wander circle
	m_vWanderTarget = Math3D::Vector4(m_dWanderRadius * cos(theta), m_dWanderRadius * sin(theta), 0.0f);

	//create a Path
	m_pPath = new Path();
	m_pPath->LoopOn();
}

SteeringBehaviors::~SteeringBehaviors()
{
	delete m_pPath;
}

Math3D::Vector4 SteeringBehaviors::Seek(Math3D::Vector4 TargetPos)
{
	Math3D::Vector4 DesiredVelocity =  /*Vec2DNormalize*/(TargetPos - m_pVehicle->Pos()) * m_pVehicle->MaxSpeed();
	DesiredVelocity.Normalize();
	return (DesiredVelocity - m_pVehicle->Velocity());
}

Math3D::Vector4 SteeringBehaviors::Flee(Math3D::Vector4 TargetPos) {

	const double PanicDistanceSq = 100.0 * 100.0; 
	
	if (Vec2DDistanceSq(m_pVehicle->Pos(), TargetPos) > PanicDistanceSq)
	{ 
		return Math3D::Vector4(0.0f, 0.0f, 0.0f);
	}

	Math3D::Vector4 DesiredVelocity = /*Vec2DNormalize*/(m_pVehicle->Pos() - TargetPos) * m_pVehicle->MaxSpeed();
	DesiredVelocity.Normalize();
	return (DesiredVelocity - m_pVehicle->Velocity());
}

Math3D::Vector4 SteeringBehaviors::Arrive(Math3D::Vector4 currentpos, Math3D::Vector4 TargetPos, Deceleration deceleration)
{
	Math3D::Vector4 ToTarget = TargetPos - m_pVehicle->Pos();
	Math3D::Vector4 DesiredVelocity =  /*Vec2DNormalize*/(TargetPos - m_pVehicle->Pos()) * m_pVehicle->MaxSpeed();
	//calculate the distance to the target position double dist = ToTarget.Length();
	double dist = sqrt(Vec2DDistanceSq(currentpos, TargetPos));
	if (dist > 0) { 
		//because Deceleration is enumerated as an int, this value is required //to provide fine tweaking of the deceleration. const double DecelerationTweaker = 0.3;		
		//calculate the speed required to reach the target given the desired //deceleration double speed = dist / ((double)deceleration * DecelerationTweaker);
		//make sure the velocity does not exceed the max speed = min(speed, m_pVehicle->MaxSpeed());
		//from here proceed just like Seek except we don't need to normalize //the ToTarget vector because we have already gone to the trouble //of calculating its length: dist. Vector2D DesiredVelocity = ToTarget * speed / dist;
		return (DesiredVelocity - m_pVehicle->Velocity());
	}
	return Math3D::Vector4(0.0f, 0.0f, 0.0f);
}

Math3D::Vector4 SteeringBehaviors::Evade(const Vehicle * pursuer, Math3D::Vector4 currentpos, Math3D::Vector4 TargetPos)
{
	/* Not necessary to include the check for facing direction this time */
	Math3D::Vector4 ToPursuer = pursuer->Pos() - m_pVehicle->Pos();

	//the look-ahead time is proportional to the distance between the pursuer 
	//and the evader; and is inversely proportional to the sum of the 
	//agents' velocities
	double LookAheadTime = /*ToPursuer.Length()*/ sqrt(Vec2DDistanceSq(currentpos, TargetPos)) / (m_pVehicle->MaxSpeed() + pursuer->Speed());

	//now flee away from predicted future position of the pursuer
	return Flee(pursuer->Pos() + pursuer->Velocity() * LookAheadTime);
}

Math3D::Vector4 SteeringBehaviors::Wander()
{
	//first, add a small random vector to the target’s position (RandomClamped 
	//returns a value between -1 and 1)
	Math3D::Vector4 m_vWanderTarget = m_vWanderTarget + Math3D::Vector4(RandomClamped() * m_dWanderJitter, RandomClamped() * m_dWanderJitter, 0.0f);

	//reproject this new vector back onto a unit circle 
	m_vWanderTarget.Normalize();

	//increase the length of the vector to the same as the radius 
	//of the wander circle 
	m_vWanderTarget *= m_dWanderRadius;

	//move the target into a position WanderDist in front of the agent 
	Math3D::Vector4 targetLocal = m_vWanderTarget + Math3D::Vector4(m_dWanderDistance, 0.0f, 0.0f);

	//project the target into world space
	Math3D::Vector4 targetWorld = PointToWorldSpace(targetLocal, m_pVehicle->Heading(), m_pVehicle->Side(), m_pVehicle->Pos()); //check the function PointToWorldSpace

	//and steer toward it 
	return targetWorld - m_pVehicle->Pos();
}

Math3D::Vector4 SteeringBehaviors::Pursuit(const Vehicle * evader)
{
	//if the evader is ahead and facing the agent then we can just seek for the evader's current position.

	Math3D::Vector4 ToEvader = evader->Pos() - m_pVehicle->Pos();

	double RelativeHeading = m_pVehicle->Heading().Dot(evader->Heading());

	if ((ToEvader.Dot(m_pVehicle->Heading()) > 0) && (RelativeHeading < -0.95))  //acos(0.95)=18 degs
	{
		return Seek(evader->Pos());
	}

	//Not considered ahead so we predict where the evader will be. The lookahead time is propotional to the distance between the evader and the pursuer; 
	//and is inversely proportional to the sum of the agent's velocities
	double LookAheadTime = ToEvader.Length() / (m_pVehicle->MaxSpeed() + evader->Speed());

	//now seek to the predicted future position of the evader
	return Seek(evader->Pos() + evader->Velocity() * LookAheadTime);
}

Math3D::Vector4 SteeringBehaviors::FollowPath()
{
	//move to next target if close enough to current target (working in distance squared space)
	if (Vec2DDistanceSq(m_pPath->CurrentWaypoint(), m_pVehicle->Pos()) < m_dWaypointSeekDistSq)
	{
		m_pPath->SetNextWaypoint();
	}

	if (!m_pPath->Finished())
	{
		return Seek(m_pPath->CurrentWaypoint());
	}

	else
	{
		return Arrive(m_pPath->CurrentWaypoint(),m_pPath->CurrentWaypoint(), normal);
	}
}



//Math3D::Vector4 SteeringBehaviors::OffsetPursuit(const Vehicle * agent, const Math3D::Vector4 offset)
//{
//	Math3D::Vector4 WorldOffsetPos = PointToWorldSpace(offset, leader->Heading(), leader->Side(), leader->Pos());
//
//	Math3D::Vector4 ToOffset = WorldOffsetPos - m_pVehicle->Pos();
//
//	//the lookahead time is propotional to the distance between the leader and the pursuer; and is inversely proportional to the sum of both
//	//agent's velocities
//	double LookAheadTime = ToOffset.Length() / (m_pVehicle->MaxSpeed() + leader->Speed());
//
//	//now Arrive at the predicted future position of the offset
//	return Arrive( ,WorldOffsetPos + leader->Velocity() * LookAheadTime,fast);
//}

double Vec2DDistanceSq(Math3D::Vector4 currentpos, Math3D::Vector4 TargetPos) 
{
	Math3D::Vector4 sub = currentpos - TargetPos;
	double res = sub*sub;
	return res;
}

//int RandomClamped() {
//	int min = -1, max = 1;
//
//	static bool first = true;
//	if (first)
//	{
//		srand(time(NULL)); //seeding for the first time only!
//		first = false;
//	}
//	return min + rand() % (max + 1 - min);
//}