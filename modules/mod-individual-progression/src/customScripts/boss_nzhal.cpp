#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "Player.h"
#include "SpellAuraEffects.h"

enum Spells
{
    SPELL_VERSE_1 = 70011,
    SPELL_VERSE_2 = 70012,
    SPELL_VERSE_3 = 70013,
    SPELL_CRESCENDO = 70014,
    SPELL_CRESCENDO_DOT = 70015,
    SPELL_SUMMON_ECHO = 70016,
};

enum Events
{
    EVENT_HEAD_CAST = 1,
    EVENT_CRESCENDO,
    EVENT_VERSE_1_TICK,
};

enum SayNzhal
{
    SAY_AGGRO = 0,
    SAY_HEAD_1,
    SAY_HEAD_2,
    SAY_HEAD_3,
    SAY_INTERRUPTED,
    SAY_CRESCENDO_0,
    SAY_CRESCENDO_1,
    SAY_CRESCENDO_2,
    SAY_CRESCENDO_3,
};

class boss_nzhal : public CreatureScript
{
public:
    boss_nzhal() : CreatureScript("boss_nzhal") { }

    struct boss_nzhalAI : public ScriptedAI
    {
        boss_nzhalAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;
        uint8 currentHead = 0;
        uint8 interruptedHeads = 0;
        bool headCasting = false;

        void Reset() override
        {
            events.Reset();
            currentHead = 0;
            interruptedHeads = 0;
            headCasting = false;
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            Talk(SAY_AGGRO);
            events.ScheduleEvent(EVENT_HEAD_CAST, 8000);
        }

        void DoCrescendo()
        {
            std::list<Player*> players;
            GetPlayerListInGrid(players, me, 100.0f);

            switch (interruptedHeads)
            {
                case 0:
                    Talk(SAY_CRESCENDO_0);
                    me->CastSpell(me, 38628, true);
                    for (Player* player : players)
                    {
                        me->CastSpell(player, 17293, true);
                        float x = player->GetPositionX() + frand(-2.f, 2.f);
                        float y = player->GetPositionY() + frand(-2.f, 2.f);
                        float z = player->GetPositionZ();
                        if (Creature* drone = me->SummonCreature(15318, x, y, z, 0.0f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 20000))
                        {
                            drone->SetReactState(REACT_AGGRESSIVE);
                            drone->Attack(player, true);
                            drone->SetInCombatWithZone();
                        }
                    }
                    break;
                case 1:
                    Talk(SAY_CRESCENDO_1);
                    me->CastSpell(me, 38628, true);
                    for (Player* player : players)
                        me->CastSpell(player, 17293, true);
                    break;
                case 2:
                    Talk(SAY_CRESCENDO_2);
                    me->CastSpell(me, 38628, true);
                    break;
                case 3:
                    Talk(SAY_CRESCENDO_3);
                    break;
            }

            currentHead = 0;
            interruptedHeads = 0;
            events.ScheduleEvent(EVENT_HEAD_CAST, 20000);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.ExecuteEvent())
            {
                case EVENT_HEAD_CAST:
                {
                    headCasting = true;
                    currentHead++;

                    std::list<Player*> players;
                    GetPlayerListInGrid(players, me, 100.0f);

                    switch (currentHead)
                    {
                        case 1:
                            Talk(SAY_HEAD_1);
                            for (uint8 i = 0; i < 4; ++i)
                                events.ScheduleEvent(EVENT_VERSE_1_TICK, i * 1000);
                            break;
                        case 2:
                            Talk(SAY_HEAD_2);
                            for (Player* player : players)
                                player->CastSpell(player, 33711, true); // Reflect Aura
                            break;
                        case 3:
                            Talk(SAY_HEAD_3);
                            for (Player* player : players)
                                player->CastSpell(player, 28194, true); // Corrupted Healing
                            break;
                    }

                    if (currentHead < 3)
                        events.ScheduleEvent(EVENT_HEAD_CAST, 10000);
                    else
                        events.ScheduleEvent(EVENT_CRESCENDO, 10000);
                    break;
                }
                case EVENT_CRESCENDO:
                    headCasting = false;
                    DoCrescendo();
                    break;
                case EVENT_VERSE_1_TICK:
                    if (Unit* tank = me->GetVictim())
                        tank->CastSpell(tank, 27177, true); // Sunder Armor
                    break;
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_nzhalAI(creature);
    }
};

void AddSC_boss_nzhal()
{
    new boss_nzhal();
}