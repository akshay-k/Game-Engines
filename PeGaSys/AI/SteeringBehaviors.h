#pragma once
#include "stdafx.h"
#include "Matrix44.h"

//the radius of the constraining circle for the wander behavior
const double WanderRad = 1.2;

//distance the wander circle is projected in front of the agent
const double WanderDist = 2.0;

//the maximum amount of displacement along the circle each frame
const double WanderJitterPerSec = 80.0;

//used in path following
const double WaypointSeekDist = 20;

class SteeringBehaviors 
{
	//struct SVector2D
	//{
	//	double x, y;
	//	SVector2D(double a = 0, double b = 0) : x(a), y(b) {}
	//};
private:

	enum behavior_type

	{

		none = 0x00000,
		seek = 0x00002,
		flee = 0x00004,
		arrive = 0x00008,
		wander = 0x00010,
		cohesion = 0x00020,
		separation = 0x00040,
		allignment = 0x00080,
		obstacle_avoidance = 0x00100,
		wall_avoidance = 0x00200,
		follow_path = 0x00400,
		pursuit = 0x00800,
		evade = 0x01000,
		interpose = 0x02000,
		hide = 0x04000,
		flock = 0x08000,
		offset_pursuit = 0x10000,
	};

	//these can be used to keep track of friends, pursuers, or prey
	Vehicle* m_pTargetAgent1;
	Vehicle* m_pTargetAgent2;

	double m_dWanderRadius; //radius of the constraining circle
	double m_dWanderDistance; //the distance the wander circle is projected in front of the agent
	double m_dWanderJitter; //maximum amount of random displacement that can be added to the target each second
	Vehicle * m_pVehicle; //Box that is the vehicle in question.
	Path * m_pPath; //pointer to any current path

	//the steering force created by the combined effect of all the selected behaviors
	Math3D::Vector4 m_vSteeringForce;

	//the current target
	Math3D::Vector4 m_vTarget;

	//the current position on the wander circle the agent is attempting to steer towards
	Math3D::Vector4 m_vWanderTarget;

	double m_dWeightSeek;
	double m_dWeightFlee;
	double m_dWeightArrive;
	double m_dWeightEvade;
	double m_dWeightWander;

	//the distance (squared) a vehicle has to be from a path waypoint before it starts seeking to the next waypoint
	double m_dWaypointSeekDistSq;

	enum Deceleration { slow = 3, normal = 2, fast = 1 };

	//default
	Deceleration m_Deceleration;

	//binary flags to indicate whether or not a behavior should be active
	int m_iFlags;

	const double   Pi = 3.14159;
	const double   TwoPi = Pi * 2;


public:

	SteeringBehaviors(Vehicle* agent);
	virtual ~SteeringBehaviors();

	//Set the Target
	void SetTarget(const Math3D::Vector4 t) { m_vTarget = t; }

	Math3D::Vector4 Seek(Math3D::Vector4 TargetPos);
	Math3D::Vector4 Flee(Math3D::Vector4 TargetPos);
	Math3D::Vector4 Arrive(Math3D::Vector4 currentpos, Math3D::Vector4 TargetPos, Deceleration deceleration); //Deceleration to be used via Physx
	Math3D::Vector4 Evade(const Vehicle* pursuer, Math3D::Vector4 currentpos, Math3D::Vector4 TargetPos); //Vechile would be the Box class...to be verified with Ravi
	Math3D::Vector4 Wander();
	Math3D::Vector4 Pursuit(const Vehicle* agent);
	//Math3D::Vector4 OffsetPursuit(const Vehicle* agent, const Math3D::Vector4 offset);
	Math3D::Vector4 FollowPath();


	//this results in a steering force that attempts to steer the vehicle to the center of the vector connecting two moving agents.
	//Math3D::Vector4 Interpose(const Vehicle* VehicleA, const Vehicle* VehicleB);

	double WanderJitter() const { return m_dWanderJitter; }
	double WanderDistance() const { return m_dWanderDistance; }
	double WanderRadius() const { return m_dWanderRadius; }

	void SetPath(std::list<Math3D::Vector4> new_path) { m_pPath->Set(new_path); }
	void CreateRandomPath(int num_waypoints, int mx, int my, int cx, int cy)const{ m_pPath->CreateRandomPath(num_waypoints, mx, my, cx, cy);}
	Math3D::Vector4 Force() const { return m_vSteeringForce; }

	bool On(behavior_type bt) { return (m_iFlags & bt) == bt; }

	void FleeOn() { m_iFlags |= flee; }
	void SeekOn() { m_iFlags |= seek; }
	void ArriveOn() { m_iFlags |= arrive; }
	void WanderOn() { m_iFlags |= wander; }
	void PursuitOn(Vehicle* v) { m_iFlags |= pursuit; m_pTargetAgent1 = v; }
	void EvadeOn(Vehicle* v) { m_iFlags |= evade; m_pTargetAgent1 = v; }

	void FleeOff() { if (On(flee))   m_iFlags ^= flee; }
	void SeekOff() { if (On(seek))   m_iFlags ^= seek; }
	void ArriveOff() { if (On(arrive)) m_iFlags ^= arrive; }
	void WanderOff() { if (On(wander)) m_iFlags ^= wander; }
	void PursuitOff() { if (On(pursuit)) m_iFlags ^= pursuit; }
	void EvadeOff() { if (On(evade)) m_iFlags ^= evade; }

	inline double RandFloat() { return ((rand()) / (RAND_MAX + 1.0)); }
	inline double RandomClamped() { return RandFloat() - RandFloat(); }
};