#include "ScriptMgr.h"
#include "ScriptedCreature.h"

enum Spells
{
    SPELL_VERSE_1 = 70011, // Armor debuff (tank killer)
    SPELL_VERSE_2 = 70012, // Reflect damage (DPS punisher)
    SPELL_VERSE_3 = 70013, // Healing = damage (healer trap)
    SPELL_CRESCENDO = 70014, // AoE scaling effect
    SPELL_CRESCENDO_DOT = 70015, // Lingering DOT
    SPELL_SUMMON_ECHO = 70016, // Summon Twisted Echo
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

        void SpellInterrupted(uint32 spellId, uint32 /*school*/) override
        {
            if (headCasting && (spellId == SPELL_VERSE_1 || spellId == SPELL_VERSE_2 || spellId == SPELL_VERSE_3))
            {
                interruptedHeads++;
                headCasting = false;
                Talk(SAY_INTERRUPTED);
                // Remove auras if needed
                for (Player* player : me->GetPlayersInRange(100.0f))
                {
                    player->RemoveAura(SPELL_VERSE_2);
                    player->RemoveAura(SPELL_VERSE_3);
                }
            }
        }

        void DoCrescendo()
        {
            switch (interruptedHeads)
            {
                case 0:
                    Talk(SAY_CRESCENDO_0);
                    DoCastAOE(38628); // Fel Explosion
                    for (Player* player : me->GetPlayersInRange(100.0f))
                    {
                        me->CastSpell(player, 17293, true); // Shadow DOT
                        float x = player->GetPositionX() + frand(-2.f, 2.f);
                        float y = player->GetPositionY() + frand(-2.f, 2.f);
                        float z = player->GetPositionZ();
                        if (Creature* add = me->SummonCreature(15318, x, y, z, 0.0f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 20000))
                            add->Attack(player, true);
                    }
                    break;
                case 1:
                    Talk(SAY_CRESCENDO_1);
                    DoCastAOE(38628);
                    for (Player* player : me->GetPlayersInRange(100.0f))
                        me->CastSpell(player, 17293, true);
                    break;
                case 2:
                    Talk(SAY_CRESCENDO_2);
                    DoCastAOE(38628);
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
                    switch (currentHead)
                    {
                        case 1:
                            Talk(SAY_HEAD_1);
                            for (uint8 i = 0; i < 4; ++i)
                                events.ScheduleEvent(EVENT_VERSE_1_TICK, i * 1000);
                            break;
                        case 2:
                            Talk(SAY_HEAD_2);
                            for (Player* player : me->GetPlayersInRange(100.0f))
                                player->AddAura(33711, player); // Spell Reflection
                            break;
                        case 3:
                            Talk(SAY_HEAD_3);
                            for (Player* player : me->GetPlayersInRange(100.0f))
                                player->AddAura(28194, player); // Corrupted Healing
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
                        tank->AddAura(27177, tank); // Sunder Armor
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
