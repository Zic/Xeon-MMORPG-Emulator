#ifndef _SHARED_PTR_H
#define _SHARED_PTR_H

//#define SHAREDPTR_DEBUGMODE // devs only, or prepare for spam, seriously.

// Meh
class AchievementInterface;
class AddonMgr;
class AIInterface;
class AlteracValley;
class ArathiBasin;
class Arena;
class ArenaTeam;
class AuctionHouse;
class AuctionMgr;
class Aura;
class AVNode;
class BaseConsole;
class BasicTaskExecutor;
class CBattleground;
class CBattlegroundManager;
class CCollideInterface;
//class CellHandler;
class ChainAggroEntity;
class Channel;
class ChannelIterator;
class ChannelMgr;
class Charter;
class ChatCommand;
class ChatHandler;
class CombatStatusHandler;
class CommandTableStorage;
class ConsoleAuthMgr;
class ConsoleSocket;
class ConsoleThread;
class Container;
class Corpse;
class Creature;
class CreatureAIScript;
class DayWatcherThread;
class DynamicObject;
class EventableObject;
class EventableObjectHolder;
class EventMgr;
class EyeOfTheStorm;
class FormationMgr;
class GameObject;
class GameObjectAIScript;
class GossipMenu;
class GossipScript;
class Group;
class Guild;
class HonorHandler;
class HookInterface;
class Instance;
class InstanceMgr;
class InstanceScript;
class Item;
class ItemInterface;
class ItemIterator;
class IVMapManager;
class LfgMatch;
class LfgMgr;
class LocalConsole;
class LocalizationMgr;
class LogonCommClientSocket;
class LogonCommHandler;
class LootMgr;
class LootRoll;
class Mailbox;
class MailSystem;
class Map;
class MapCell;
class MapMgr;
class MapScriptInterface;
class Master;
class MovementInfo;
class NewsAnnouncer;
class Object;
class ObjectMgr;
class Pet;
class Player;
class QuestLogEntry;
class QuestMgr;
class QuestScript;
class RemoteConsole;
class ScriptMgr;
class SkillIterator;
class SkillNameMgr;
class Spell;
class SpellCastTargets;
class StructFactory;
class SubGroup;
class Task;
class TaskExecutor;
class TaskList;
class TaxiMgr;
class TaxiPath;
class TerrainMgr;
class Transporter;
class TransportPath;
class Unit;
class UpdateMask;
class Vehicle;
class WarsongGulch;
class WeatherInfo;
class WeatherMgr;
class WordFilter;
class World;
class WorldRunnable;
class WorldSession;
class WorldSocket;
class WorldStateManager;
class WorldStateTemplateManager;

// Typedefs for readable code
typedef shared_ptr<CBattleground> BattlegroundPointer;
typedef shared_ptr<CBattlegroundManager> BattlegroundMgrPointer;
typedef shared_ptr<AchievementInterface> AchievementInterfacePointer;
typedef shared_ptr<AddonMgr> AddonMgrPointer;
typedef shared_ptr<AIInterface> AIInterfacePointer;
typedef shared_ptr<AlteracValley> AlteracValleyPointer;
typedef shared_ptr<ArathiBasin> ArathiBasinPointer;
typedef shared_ptr<Arena> ArenaPointer;
typedef shared_ptr<ArenaTeam> ArenaTeamPointer;
typedef shared_ptr<AuctionHouse> AuctionHousePointer;
typedef shared_ptr<AuctionMgr> AuctionMgrPointer;
typedef shared_ptr<Aura> AuraPointer;
typedef shared_ptr<AVNode> AVNodePointer;
typedef shared_ptr<BaseConsole> BaseConsolePointer;
typedef shared_ptr<BasicTaskExecutor> BasicTaskExecutorPointer;
typedef shared_ptr<CBattleground> CBattlegroundPointer;
typedef shared_ptr<CBattlegroundManager> CBattlegroundManagerPointer;
typedef shared_ptr<CCollideInterface> CCollideInterfacePointer;
//typedef shared_ptr<CellHandler> CellHandlerPointer;
typedef shared_ptr<ChainAggroEntity> ChainAggroEntityPointer;
typedef shared_ptr<Channel> ChannelPointer;
typedef shared_ptr<ChannelIterator> ChannelIteratorPointer;
typedef shared_ptr<ChannelMgr> ChannelMgrPointer;
typedef shared_ptr<Charter> CharterPointer;
typedef shared_ptr<ChatCommand> ChatCommandPointer;
typedef shared_ptr<ChatHandler> ChatHandlerPointer;
typedef shared_ptr<CombatStatusHandler> CombatStatusHandlerPointer;
typedef shared_ptr<CommandTableStorage> CommandTableStoragePointer;
typedef shared_ptr<ConsoleAuthMgr> ConsoleAuthMgrPointer;
typedef shared_ptr<ConsoleSocket> ConsoleSocketPointer;
typedef shared_ptr<ConsoleThread> ConsoleThreadPointer;
typedef shared_ptr<Container> ContainerPointer;
typedef shared_ptr<Corpse> CorpsePointer;
typedef shared_ptr<Creature> CreaturePointer;
typedef shared_ptr<CreatureAIScript> CreatureAIScriptPointer;
typedef shared_ptr<DayWatcherThread> DayWatcherThreadPointer;
typedef shared_ptr<DynamicObject> DynamicObjectPointer;
typedef shared_ptr<EventableObject> EventableObjectPointer;
typedef shared_ptr<EventableObjectHolder> EventableObjectHolderPointer;
typedef shared_ptr<EventMgr> EventMgrPointer;
typedef shared_ptr<EyeOfTheStorm> EyeOfTheStormPointer;
typedef shared_ptr<FormationMgr> FormationMgrPointer;
typedef shared_ptr<GameObject> GameObjectPointer;
typedef shared_ptr<GameObjectAIScript> GameObjectAIScriptPointer;
typedef shared_ptr<GossipMenu> GossipMenuPointer;
typedef shared_ptr<GossipScript> GossipScriptPointer;
typedef shared_ptr<Group> GroupPointer;
typedef shared_ptr<Guild> GuildPointer;
typedef shared_ptr<HonorHandler> HonorHandlerPointer;
typedef shared_ptr<HookInterface> HookInterfacePointer;
typedef shared_ptr<Instance> InstancePointer;
typedef shared_ptr<InstanceMgr> InstanceMgrPointer;
typedef shared_ptr<InstanceScript> InstanceScriptPointer;
typedef shared_ptr<Item> ItemPointer;
typedef shared_ptr<ItemInterface> ItemInterfacePointer;
typedef shared_ptr<ItemIterator> ItemIteratorPointer;
typedef shared_ptr<IVMapManager> IVMapManagerPointer;
typedef shared_ptr<LfgMatch> LfgMatchPointer;
typedef shared_ptr<LfgMgr> LfgMgrPointer;
typedef shared_ptr<LocalConsole> LocalConsolePointer;
typedef shared_ptr<LocalizationMgr> LocalizationMgrPointer;
typedef shared_ptr<LogonCommClientSocket> LogonCommClientSocketPointer;
typedef shared_ptr<LogonCommHandler> LogonCommHandlerPointer;
typedef shared_ptr<LootMgr> LootMgrPointer;
typedef shared_ptr<LootRoll> LootRollPointer;
typedef shared_ptr<Mailbox> MailboxPointer;
typedef shared_ptr<MailSystem> MailSystemPointer;
typedef shared_ptr<Map> MapPointer;
typedef shared_ptr<MapCell> MapCellPointer;
typedef shared_ptr<MapMgr> MapMgrPointer;
typedef shared_ptr<MapScriptInterface> MapScriptInterfacePointer;
typedef shared_ptr<Master> MasterPointer;
typedef shared_ptr<MovementInfo> MovementInfoPointer;
typedef shared_ptr<NewsAnnouncer> NewsAnnouncerPointer;
typedef shared_ptr<Object> ObjectPointer;
typedef shared_ptr<ObjectMgr> ObjectMgrPointer;
typedef shared_ptr<Player> PlayerPointer;
typedef shared_ptr<QuestLogEntry> QuestLogEntryPointer;
typedef shared_ptr<QuestMgr> QuestMgrPointer;
typedef shared_ptr<QuestScript> QuestScriptPointer;
typedef shared_ptr<RemoteConsole> RemoteConsolePointer;
typedef shared_ptr<ScriptMgr> ScriptMgrPointer;
typedef shared_ptr<SkillIterator> SkillIteratorPointer;
typedef shared_ptr<SkillNameMgr> SkillNameMgrPointer;
typedef shared_ptr<Spell> SpellPointer;
typedef shared_ptr<SpellCastTargets> SpellCastTargetsPointer;
typedef shared_ptr<StructFactory> StructFactoryPointer;
typedef shared_ptr<SubGroup> SubGroupPointer;
typedef shared_ptr<Task> TaskPointer;
typedef shared_ptr<TaskExecutor> TaskExecutorPointer;
typedef shared_ptr<TaskList> TaskListPointer;
typedef shared_ptr<TaxiMgr> TaxiMgrPointer;
typedef shared_ptr<TaxiPath> TaxiPathPointer;
typedef shared_ptr<TerrainMgr> TerrainMgrPointer;
typedef shared_ptr<Transporter> TransporterPointer;
typedef shared_ptr<TransportPath> TransportPathPointer;
typedef shared_ptr<Unit> UnitPointer;
typedef shared_ptr<UpdateMask> UpdateMaskPointer;
typedef shared_ptr<Vehicle> VehiclePointer;
typedef shared_ptr<WarsongGulch> WarsongGulchPointer;
typedef shared_ptr<WeatherInfo> WeatherInfoPointer;
typedef shared_ptr<WeatherMgr> WeatherMgrPointer;
typedef shared_ptr<WordFilter> WordFilterPointer;
typedef shared_ptr<World> WorldPointer;
typedef shared_ptr<WorldRunnable> WorldRunnablePointer;
typedef shared_ptr<WorldSession> WorldSessionPointer;
typedef shared_ptr<WorldSocket> WorldSocketPointer;
typedef shared_ptr<WorldStateManager> WorldStateManagerPointer;
typedef shared_ptr<WorldStateTemplateManager> WorldStateTemplateManagerPointer;


#define CAST(x,y) std::tr1::static_pointer_cast<x>(y)

#define TO_PLAYER(ptr) CAST(Player,ptr)
#define TO_UNIT(ptr) CAST(Unit,ptr)
#define TO_CREATURE(ptr) CAST(Creature,ptr)
#define TO_PET(ptr) CAST(Pet,ptr)
#define TO_CONTAINER(ptr) CAST(Container,ptr)
#define TO_ITEM(ptr) CAST(Item,ptr)
#define TO_OBJECT(ptr) CAST(Object,ptr)
#define TO_GAMEOBJECT(ptr) CAST(GameObject,ptr)
#define TO_DYNAMICOBJECT(ptr) CAST(DynamicObject,ptr)
#define TO_CORPSE(ptr) CAST(Corpse,ptr)
#define TO_EVENTABLEOBJECT(ptr) CAST(EventableObject,ptr)
#define TO_CBATTLEGROUND(ptr) CAST(CBattleground,ptr)
#define TO_CBATTLEGROUNDMGR(ptr) CAST(CBattlegroundManager,ptr)
#define TO_ALTERACVALLEY(ptr) CAST(AlteracValley,ptr)
#define TO_EYEOFTHESTORM(ptr) CAST(EyeOfTheStorm,ptr)
#define TO_WARSONGGULCH(ptr) CAST(WarsongGulch,ptr)
#define TO_ARENA(ptr) CAST(Arena,ptr)
#define TO_ARATHIBASIN(ptr) CAST(ArathiBasin,ptr)
#define TO_TRANSPORT(ptr) CAST(Transporter,ptr)
#define TO_AURA(ptr) CAST(Aura,ptr)
#define TO_SPELL(ptr) CAST(Spell,ptr)
#define TO_LOOTROLL(ptr) CAST(LootRoll,ptr)
#define TO_VEHICLE(ptr) CAST(Vehicle,ptr)
#define TO_PTR(classname, ptr) CAST(classname,ptr)

#define NULLPTR shared_ptr<void>()
#define NULLGOB shared_ptr<GameObject>()
#define NULLPLR shared_ptr<Player>()
#define NULLOBJ shared_ptr<Object>()
#define NULLGOB shared_ptr<GameObject>()
#define NULLUNIT shared_ptr<Unit>()
#define NULLPET shared_ptr<Pet>()
#define NULLITEM shared_ptr<Item>()
#define NULLDYN shared_ptr<DynamicObject>()
#define NULLCREATURE shared_ptr<Creature>()
#define NULLVEHICLE shared_ptr<Vehicle>()
#define NULLCORPSE shared_ptr<Corpse>()
#define NULLTRANSPORT shared_ptr<Transporter>()
#define NULLEVENTABLEOBJECT shared_ptr<EventableObject>()
#define NULLCONTAINER shared_ptr<Container>()
#define NULLMAPMGR shared_ptr<MapMgr>()
#define NULLBGMGR shared_ptr<CBattlegroundManager>()
#define NULLBATTLEGROUND shared_ptr<CBattleground>()
#define NULLWEATHER shared_ptr<WeatherInfo>()
#define NULLWORLD shared_ptr<World>()
#define NULLINSTANCEMGR shared_ptr<InstanceMgr>()
#define NULLSPELL shared_ptr<Spell>()
#define NULLAURA shared_ptr<Aura>()
#define NULLROLL shared_ptr<LootRoll>()
#define NULLMAPMGR shared_ptr<MapMgr>()
#define NULLMISC(class_name) shared_ptr<class_name>()

#define object_shared_from_this() TO_OBJECT(shared_from_this())
#define obj_shared_from_this() TO_OBJECT(shared_from_this())
#define gob_shared_from_this() TO_GAMEOBJECT(shared_from_this())
#define unit_shared_from_this() TO_UNIT(shared_from_this())
#define plr_shared_from_this() TO_PLAYER(shared_from_this())
#define player_shared_from_this() TO_PLAYER(shared_from_this())
#define dyn_shared_from_this() TO_DYNAMICOBJECT(shared_from_this())
#define item_shared_from_this() TO_ITEM(shared_from_this())
#define creature_shared_from_this() TO_CREATURE(shared_from_this())
#define pet_shared_from_this() TO_PET(shared_from_this())
#define spell_shared_from_this() TO_SPELL(shared_from_this())
#define aura_shared_from_this() TO_AURA(shared_from_this())
#define lootroll_shared_from_this() TO_LOOTROLL(shared_from_this())
#define vehicle_shared_from_this() TO_VEHICLE(shared_from_this())
#define class_shared_from_this(x) TO_PTR(x, shared_from_this())

#endif