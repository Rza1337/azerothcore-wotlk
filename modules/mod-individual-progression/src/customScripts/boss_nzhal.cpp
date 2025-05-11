#include "ScriptMgr.h"
#include "ScriptedCreature.h"

enum Spells
{
    SPELL_SHADOW_BOLT = 9613,    // Example spell
    SPELL_ENRAGE      = 8599     // Generic enrage
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
            shadowBoltTimer = 5s;
            enraged = false;
        }

        void EnterCombat(Unit* /*who*/) override { }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (shadowBoltTimer <= 0s)
            {
                DoCastVictim(SPELL_SHADOW_BOLT);
                shadowBoltTimer = 5s;
            }
            else
                shadowBoltTimer -= diff;

            if (!enraged && me->HealthBelowPct(30))
            {
                DoCast(me, SPELL_ENRAGE);
                enraged = true;
            }

            DoMeleeAttackIfReady();
        }

    private:
        Time shadowBoltTimer;
        bool enraged;
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
