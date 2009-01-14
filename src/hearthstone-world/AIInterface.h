/*
 * Aspire Hearthstone
 * Copyright (C) 2008 - 2009 AspireDev <http://www.aspiredev.org/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef WOWSERVER_AIINTERFACE_H
#define WOWSERVER_AIINTERFACE_H

/* platforms that already define M_PI in math.h */
#ifdef M_PI
#undef M_PI
#endif

#define M_PI	   3.14159265358979323846
#define UNIT_MOVEMENT_INTERPOLATE_INTERVAL 400/*750*/ // ms smoother server/client side moving vs less cpu/ less b/w
#define TARGET_UPDATE_INTERVAL 600 // ms
#define oocr 50.0f // out of combat range
#define PLAYER_SIZE 1.5f

#define ENABLE_CREATURE_DAZE
#ifdef ENABLE_CREATURE_DAZE
	#define CREATURE_SPELL_TO_DAZE 1604
	#define CREATURE_DAZE_TRIGGER_ANGLE M_PI/2 //for the beginners this means 45 degrees 
#endif

#define DISTANCE_TO_SMALL_TO_WALK 1.0f

class Object;
class Creature;
class Unit;
class Player;
class WorldSession;
class SpellCastTargets;


enum AIType
{
	AITYPE_LONER,
	AITYPE_AGRO,
	AITYPE_SOCIAL,
	AITYPE_PET,
	AITYPE_TOTEM,
	AITYPE_GUARDIAN, //we got a master but he cannot control us, we follow and battle oposite factions
};

enum MovementType
{
	MOVEMENTTYPE_NONE,
	MOVEMENTTYPE_RANDOMWP,
	MOVEMENTTYPE_CIRCLEWP,
	MOVEMENTTYPE_WANTEDWP,
	MOVEMENTTYPE_DONTMOVEWP,
	MOVEMENTTYPE_QUEST = 10,
	MOVEMENTTYPE_FORWARDTHANSTOP = 11,
};


/*struct AI_Target
{
	UnitPointer target;
	int32 threat;
};*/


enum AI_Agent
{
	AGENT_NULL,
	AGENT_MELEE,
	AGENT_RANGED,
	AGENT_FLEE,
	AGENT_SPELL,
	AGENT_CALLFORHELP
};

enum AI_SpellType
{
	STYPE_NULL,
	STYPE_ROOT,
	STYPE_HEAL,
	STYPE_STUN,
	STYPE_FEAR,
	STYPE_SILENCE,
	STYPE_CURSE,
	STYPE_AOEDAMAGE,
	STYPE_DAMAGE,
	STYPE_SUMMON,
	STYPE_BUFF,
	STYPE_DEBUFF
};

enum AI_SpellTargetType
{
	TTYPE_NULL,
	TTYPE_SINGLETARGET,
	TTYPE_DESTINATION,
	TTYPE_SOURCE,
	TTYPE_CASTER,
	TTYPE_OWNER,
};

enum AI_State
{
	STATE_IDLE,
	STATE_ATTACKING,
	STATE_CASTING,
	STATE_FLEEING,
	STATE_FOLLOWING,
	STATE_EVADE,
	STATE_MOVEWP,
	STATE_FEAR,
	STATE_WANDER,
	STATE_STOPPED,
	STATE_SCRIPTMOVE,
	STATE_SCRIPTIDLE
};

enum MovementState
{
	MOVEMENTSTATE_MOVE,
	MOVEMENTSTATE_FOLLOW,
	MOVEMENTSTATE_STOP,
	MOVEMENTSTATE_FOLLOW_OWNER
};

enum CreatureState
{
	STOPPED,
	MOVING,
	ATTACKING
};

enum AiEvents
{
	EVENT_ENTERCOMBAT,
	EVENT_LEAVECOMBAT,
	EVENT_DAMAGETAKEN,
	EVENT_FEAR,
	EVENT_UNFEAR,
	EVENT_FOLLOWOWNER,
	EVENT_WANDER,
	EVENT_UNWANDER,
	EVENT_UNITDIED,
};

struct SpellEntry;
//enum MOD_TYPES;

struct AI_Spell
{
	~AI_Spell() { autocast_type=(uint32)-1; }

	uint32 entryId;
	uint16 agent;
	uint32 procChance;
	uint32 procCount;
	SpellEntry * spell;
	uint8 spellType;
	uint8 spelltargetType;
	uint32 cooldown;
	uint32 cooldowntime;
	float floatMisc1;
	uint32 Misc2;

	uint32 procCounter;
	float minrange;
	float maxrange;
	int32 autocast_type;
	bool custom_pointer;

	bool first_use;
};

bool isGuard(uint32 id);
uint32 getGuardId(uint32 id);


typedef std::tr1::unordered_map<shared_ptr<Unit>, int32> TargetMap;
namespace std
{
	namespace tr1
	{
		template <>
		class hash < UnitPointer > : public unary_function<shared_ptr<Unit>, size_t>
		{
		public:
			size_t operator()(UnitPointer __x) const
			{
				return (size_t)__x.get();
			}
		};
	};
};

typedef std::set<shared_ptr<Unit> > AssistTargetSet;
typedef std::map<uint32, AI_Spell*> SpellMap;

class ChainAggroEntity;
class SERVER_DECL AIInterface
{
public:

	AIInterface();
	~AIInterface();

	// Misc
	void Init(shared_ptr<Unit>un, AIType at, MovementType mt);
	void Init(shared_ptr<Unit>un, AIType at, MovementType mt, shared_ptr<Unit>owner); // used for pets
	shared_ptr<Unit>GetUnit() { return m_Unit; }
	shared_ptr<Unit>GetPetOwner() { return m_PetOwner; }
	void DismissPet();
	void SetUnitToFollow(UnitPointer un) { UnitToFollow = un; };
	void SetUnitToFear(UnitPointer un)  { UnitToFear = un; };
	void SetFollowDistance(float dist) { FollowDistance = dist; };
	void SetUnitToFollowAngle(float angle) { m_fallowAngle = angle; }
	bool setInFront(UnitPointer target);
	HEARTHSTONE_INLINE UnitPointer getUnitToFollow() { return UnitToFollow; }
	void setCreatureState(CreatureState state){ m_creatureState = state; }
	HEARTHSTONE_INLINE uint8 getAIState() { return m_AIState; }
	HEARTHSTONE_INLINE uint8 getAIType() { return m_AIType; }
	HEARTHSTONE_INLINE uint8 getCurrentAgent() { return m_aiCurrentAgent; }
	void setCurrentAgent(AI_Agent agent) { m_aiCurrentAgent = agent; }
	uint32	getThreatByGUID(uint64 guid);
	uint32	getThreatByPtr(UnitPointer obj);
	UnitPointer GetMostHated();
	UnitPointer GetSecondHated();
	bool	modThreatByGUID(uint64 guid, int32 mod);
	bool	modThreatByPtr(UnitPointer obj, int32 mod);
	void	RemoveThreatByPtr(UnitPointer obj);
	HEARTHSTONE_INLINE AssistTargetSet GetAssistTargets() { return m_assistTargets; }
	HEARTHSTONE_INLINE TargetMap *GetAITargets() { return &m_aiTargets; }
	void addAssistTargets(UnitPointer Friends);
	void ClearHateList();
	void WipeHateList();
	void WipeTargetList();
	bool taunt(UnitPointer caster, bool apply = true);
	UnitPointer getTauntedBy();
	bool GetIsTaunted();
	HEARTHSTONE_INLINE size_t getAITargetsCount() { return m_aiTargets.size(); }
	HEARTHSTONE_INLINE uint32 getOutOfCombatRange() { return m_outOfCombatRange; }
	void setOutOfCombatRange(uint32 val) { m_outOfCombatRange = val; }

	// Spell
	uint8 CastSpell(UnitPointer caster, SpellEntry *spellInfo, SpellCastTargets targets);
	SpellEntry *getSpellEntry(uint32 spellId);
	SpellCastTargets setSpellTargets(SpellEntry *spellInfo, UnitPointer target);
	AI_Spell *getSpell();
	void addSpellToList(AI_Spell *sp);
	//don't use this until i finish it !!
//	void CancelSpellCast();

	// Event Handler
	void HandleEvent(uint32 event, UnitPointer pUnit, uint32 misc1);
	void OnDeath(ObjectPointer pKiller);
	void AttackReaction(shared_ptr<Unit>pUnit, uint32 damage_dealt, uint32 spellId = 0);
	bool HealReaction(UnitPointer caster, UnitPointer victim, uint32 amount, SpellEntry * sp);
	void Event_Summon_EE_totem(uint32 summon_duration);
	void Event_Summon_FE_totem(uint32 summon_duration);

	// Update
	void Update(uint32 p_time);
	void UpdateCivilian();

	// Movement
	void SendMoveToPacket(float toX, float toY, float toZ, float toO, uint32 time, uint32 MoveFlags);
	//void SendMoveToSplinesPacket(std::list<Waypoint> wp, bool run);
	void MoveTo(float x, float y, float z, float o);
	uint32 getMoveFlags();
	void UpdateMove();
	void SendCurrentMove(PlayerPointer plyr/*uint64 guid*/);
	void StopMovement(uint32 time);
	uint32 getCurrentWaypoint() { return m_currentWaypoint; }
	void changeWayPointID(uint32 oldwpid, uint32 newwpid);
	bool addWayPoint(WayPoint* wp);
	bool saveWayPoints();
	bool showWayPoints(PlayerPointer pPlayer, bool Backwards);
	bool hideWayPoints(PlayerPointer pPlayer);
	WayPoint* getWayPoint(uint32 wpid);
	void deleteWayPoint(uint32 wpid);
	void deleteWaypoints();
	HEARTHSTONE_INLINE bool hasWaypoints() { return m_waypoints!=NULL; }
	HEARTHSTONE_INLINE void setMoveType(uint32 movetype) { m_moveType = movetype; }
	HEARTHSTONE_INLINE uint32 getMoveType() { return m_moveType; }
	HEARTHSTONE_INLINE void setMoveRunFlag(bool f) { m_moveRun = f; }
	HEARTHSTONE_INLINE bool getMoveRunFlag() { return m_moveRun; }
	void setWaypointToMove(uint32 id) { m_currentWaypoint = id; }
	bool IsFlying();

	// Calculation
	float _CalcAggroRange(UnitPointer target);
	void _CalcDestinationAndMove(shared_ptr<Unit>target, float dist);
	float _CalcCombatRange(UnitPointer target, bool ranged);
	float _CalcDistanceFromHome();
	uint32 _CalcThreat(uint32 damage, SpellEntry * sp, UnitPointer Attacker);
	
	void SetAllowedToEnterCombat(bool val) { m_AllowedToEnterCombat = val; }
	HEARTHSTONE_INLINE bool GetAllowedToEnterCombat(void) { return m_AllowedToEnterCombat; }

	void CheckTarget(UnitPointer target);
	HEARTHSTONE_INLINE void SetAIState(AI_State newstate) { m_AIState = newstate; }

	// Movement
	bool m_canMove;
	bool m_WayPointsShowing;
	bool m_WayPointsShowBackwards;
	uint32 m_currentWaypoint;
	bool m_moveBackward;
	uint32 m_moveType;
	bool m_moveRun;
	bool m_moveFly;
	bool m_moveSprint;
	CreatureState m_creatureState;
	size_t GetWayPointsCount()
	{
		if(m_waypoints && !m_waypoints->empty())
			return m_waypoints->size()-1;	/* ignore 0 */
		else
			return 0;
	}
	bool m_canFlee;
	bool m_canCallForHelp;
	bool m_canRangedAttack;
	uint32 m_RangedAttackSpell;
	uint32 m_SpellSoundid;

	float m_FleeHealth;
	uint32 m_FleeDuration;
	float m_CallForHelpHealth;
	uint32 m_totemspelltimer;
	uint32 m_totemspelltime;
	SpellEntry * totemspell;

	ChainAggroEntity* m_ChainAgroSet;

	float m_sourceX, m_sourceY, m_sourceZ;
	uint32 m_totalMoveTime;
	HEARTHSTONE_INLINE void AddStopTime(uint32 Time) { m_moveTimer += Time; }
	HEARTHSTONE_INLINE void SetNextSpell(AI_Spell*sp) { m_nextSpell = sp; }
	HEARTHSTONE_INLINE UnitPointer GetNextTarget() { return m_nextTarget; }
	HEARTHSTONE_INLINE void SetNextTarget (shared_ptr<Unit>nextTarget) 
	{ 
		m_nextTarget = nextTarget; 
		if(nextTarget)
		{
			m_Unit->SetUInt64Value(UNIT_FIELD_TARGET, m_nextTarget->GetGUID());
#ifdef ENABLE_GRACEFULL_HIT
			have_graceful_hit=false;
#endif
		}
		else m_Unit->SetUInt64Value(UNIT_FIELD_TARGET, 0);
	}

	/*HEARTHSTONE_INLINE void ResetProcCounts()
	{
		AI_Spell*sp;
		for(list<AI_Spell*>::iterator itr = m_spells.begin(); itr != m_spells.end(); ++itr)
				{
					sp = *itr;
					sp->procCount =sp->procCountDB;
				}
	}*/

	CreaturePointer m_formationLinkTarget;
	float m_formationFollowDistance;
	float m_formationFollowAngle;
	uint32 m_formationLinkSqlId;

	void WipeReferences();
	WayPointMap *m_waypoints;
	HEARTHSTONE_INLINE void SetPetOwner(UnitPointer owner) { m_PetOwner = owner; }
 
	list<AI_Spell*> m_spells;

	bool disable_combat;

	bool disable_melee;
	bool disable_ranged;
	bool disable_spell;
	bool disable_targeting;

	bool waiting_for_cooldown;

	uint32 next_spell_time;
	AI_Spell * last_found_spell;

	void CheckNextSpell(AI_Spell*sp)
	{
		if(m_nextSpell == sp)
			m_nextSpell = 0;
	}

	void ResetProcCounts();

	HEARTHSTONE_INLINE void SetWaypointMap(WayPointMap * m) { m_waypoints = m; }
	bool m_isGuard;
//	bool m_fastMove;
	void setGuardTimer(uint32 timer) { m_guardTimer = timer; }
	void _UpdateCombat(uint32 p_time);

protected:
	bool m_AllowedToEnterCombat;

	// Update
	void _UpdateTargets();
	void _UpdateMovement(uint32 p_time);
	void _UpdateTimer(uint32 p_time);
	int m_updateAssist;
	int m_updateTargets;
	uint32 m_updateAssistTimer;
	uint32 m_updateTargetsTimer;

	// Misc
	bool firstLeaveCombat;
	UnitPointer FindTarget();
	UnitPointer FindTargetForSpell(AI_Spell *sp);
	UnitPointer FindHealTargetForSpell(AI_Spell *sp);
	bool FindFriends(float dist);
	AI_Spell *m_nextSpell;
	UnitPointer m_nextTarget;
	uint32 m_fleeTimer;
	bool m_hasFled;
	bool m_hasCalledForHelp;
	uint32 m_outOfCombatRange;

	shared_ptr<Unit>m_Unit;
	shared_ptr<Unit>m_PetOwner;
	CreaturePointer m_summonedGuard;
	uint32 m_guardCallTimer;
	float FollowDistance;
	float FollowDistance_backup;
	float m_fallowAngle;

	//std::set<AI_Target> m_aiTargets;
	TargetMap m_aiTargets;
	AssistTargetSet m_assistTargets;
	AIType m_AIType;
	AI_State m_AIState;
	AI_Agent m_aiCurrentAgent;

	UnitPointer tauntedBy; //This mob will hit only tauntedBy mob.
	bool isTaunted;
	UnitPointer soullinkedWith; //This mob can be hitten only by soullinked unit
	bool isSoulLinked;


	// Movement
	float m_walkSpeed;
	float m_runSpeed;
	float m_flySpeed;
	float m_destinationX;
	float m_destinationY;
	float m_destinationZ;
	
	float m_nextPosX;
	float m_nextPosY;
	float m_nextPosZ;

	//Return position after attacking a mob
	float m_returnX;
	float m_returnY;
	float m_returnZ;

	float m_lastFollowX;
	float m_lastFollowY;
	//typedef std::map<uint32, WayPoint*> WayPointMap;
	shared_ptr<Unit>UnitToFollow;
	shared_ptr<Unit>UnitToFollow_backup;//used unly when forcing creature to wander (blind spell) so when effect wears off we can follow our master again (guardian)
	shared_ptr<Unit>UnitToFear;
	uint32 m_timeToMove;
	uint32 m_timeMoved;
	uint32 m_moveTimer;
	uint32 m_FearTimer;
	uint32 m_WanderTimer;

	MovementType m_MovementType;
	MovementState m_MovementState;
	uint32 m_guardTimer;
	int32 m_currentHighestThreat;
public:
	bool m_is_in_instance;
	bool skip_reset_hp;

	void WipeCurrentTarget();
	bool CheckCurrentTarget();
	bool TargetUpdateCheck(UnitPointer ptr);
};
#endif
