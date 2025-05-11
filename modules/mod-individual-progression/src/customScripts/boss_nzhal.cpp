#include "ScriptMgr.h"
#include "ScriptedCreature.h"

enum Spells
{
    SPELL_SHADOW_BOLT = 9613,
    SPELL_ENRAGE = 8599
};

enum Events
{
    EVENT_SHADOW_BOLT = 1,
    EVENT_ENRAGE = 2
};

class boss_nzhal : public CreatureScript
{
public:
    boss_nzhal() : CreatureScript("boss_nzhal") { }

    struct boss_nzhalAI : public ScriptedAI
    {
        boss_nzhalAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;
        bool enraged;

        void Reset() override
        {
            events.Reset();
            enraged = false;
            events.ScheduleEvent(EVENT_SHADOW_BOLT, 5000);
            events.ScheduleEvent(EVENT_ENRAGE, 1000);
        }

        void JustEngagedWith(Unit* who) override
        {
            me->CallForHelp(60.0f);
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
                case EVENT_SHADOW_BOLT:
                    DoCastVictim(SPELL_SHADOW_BOLT);
                    events.ScheduleEvent(EVENT_SHADOW_BOLT, 5000);
                    break;

                case EVENT_ENRAGE:
                    if (!enraged && me->HealthBelowPct(30))
                    {
                        DoCast(me, SPELL_ENRAGE);
                        enraged = true;
                    }
                    else
                    {
                        events.ScheduleEvent(EVENT_ENRAGE, 1000);
                    }
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
