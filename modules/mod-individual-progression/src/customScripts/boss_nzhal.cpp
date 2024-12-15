#include "ScriptMgr.h"
#include "ScriptedCreature.h"

enum Spells
{
    SPELL_TENTACLE_SLAM = 6524,
    SPELL_INK_CLOUD = 44198,
    SPELL_CALL_OF_THE_ABYSS = 59414,
    SPELL_CRUSHING_MAW = 33661,
    SPELL_TIDAL_SURGE = 37405,
    SPELL_BERSERK = 27680
};

enum Texts
{
    SAY_AGGRO = 0,
    SAY_DEATH = 1
};

class boss_nzhal : public CreatureScript
{
public:
    boss_nzhal() : CreatureScript("boss_nzhal") { }

    struct boss_nzhalAI : public ScriptedAI
    {
        boss_nzhalAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            me->SetDisableGravity(true);
            me->SetCanFly(true);
            me->SetReactState(REACT_AGGRESSIVE);
        }

        void EnterCombat(Unit* who) override
        {
            Talk(SAY_AGGRO);
            events.ScheduleEvent(1, 10000); // Example event scheduling
        }

        void JustDied(Unit* /*killer*/) override
        {
            Talk(SAY_DEATH);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case 1:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        {
                            DoCast(target, SPELL_TENTACLE_SLAM);
                        }
                        events.ScheduleEvent(1, 15000);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_nzhalAI(creature);
    }
};
