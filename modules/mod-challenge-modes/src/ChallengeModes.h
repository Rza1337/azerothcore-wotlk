#ifndef CHALLENGEMODES_H
#define CHALLENGEMODES_H

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Item.h"
#include "ItemTemplate.h"
#include "GameObjectAI.h"
#include "Pet.h"
#include <map>
#include <unordered_map>

enum ChallengeModeSettings
{
    SETTING_HARDCORE           = 0,
    SETTING_SEMI_HARDCORE      = 1,
    SETTING_SELF_CRAFTED       = 2,
    SETTING_ITEM_QUALITY_LEVEL = 3,
    SETTING_SLOW_XP_GAIN       = 4,
    SETTING_VERY_SLOW_XP_GAIN  = 5,
    SETTING_QUEST_XP_ONLY      = 6,
    SETTING_IRON_MAN           = 7,
    HARDCORE_DEAD              = 8,
    SETTING_PACIFIST           = 9,
    SETTING_TURTLE_MODE        = 10,
    SETTING_QUESTLESS          = 11,
    SETTING_CASHLESS           = 12
};

enum AllowedProfessions
{
    RUNEFORGING    = 53428,
    POISONS        = 2842,
    BEAST_TRAINING = 5149
};

class ChallengeModes
{
public:
    static ChallengeModes* instance();

    bool challengesEnabled, hardcoreEnable, semiHardcoreEnable, selfCraftedEnable, itemQualityLevelEnable, slowXpGainEnable, verySlowXpGainEnable, turtleModeEnable, questXpOnlyEnable, ironManEnable, pacifistEnable, questlessEnable, cashlessEnable;
    uint32 hardcoreDisableLevel, semiHardcoreDisableLevel, selfCraftedDisableLevel, itemQualityLevelDisableLevel, slowXpGainDisableLevel, verySlowXpGainDisableLevel, turtleModeDisableLevel, questXpOnlyDisableLevel, ironManDisableLevel, pacifistDisableLevel, questlessDisableLevel, cashlessDisableLevel;
    uint32 hardcoreItemRewardAmount, semiHardcoreItemRewardAmount, selfCraftedItemRewardAmount, itemQualityLevelItemRewardAmount, slowXpGainItemRewardAmount, verySlowXpGainItemRewardAmount, turtleModeXpGainItemRewardAmount, questXpOnlyItemRewardAmount, ironManItemRewardAmount, pacifistItemRewardAmount, questlessItemRewardAmount, cashlessItemRewardAmount;
    float hardcoreXpBonus, semiHardcoreXpBonus, selfCraftedXpBonus, itemQualityLevelXpBonus, questXpOnlyXpBonus, slowXpGainBonus, verySlowXpGainBonus, turtleModeXpGainBonus, ironManXpBonus, pacifistXpBonus, questlessXpBonus, cashlessXpBonus;

    std::unordered_map<uint8, uint32> hardcoreTitleRewards, semiHardcoreTitleRewards, selfCraftedTitleRewards, itemQualityLevelTitleRewards, slowXpGainTitleRewards, verySlowXpGainTitleRewards, turtleModeXpGainTitleRewards, questXpOnlyTitleRewards, ironManTitleRewards, pacifistTitleRewards, questlessTitleRewards, cashlessTitleRewards;
    std::unordered_map<uint8, uint32> hardcoreItemRewards, semiHardcoreItemRewards, selfCraftedItemRewards, itemQualityLevelItemRewards, slowXpGainItemRewards, verySlowXpGainItemRewards, turtleModeXpGainItemRewards, questXpOnlyItemRewards, ironManItemRewards, pacifistItemRewards, questlessItemRewards, cashlessItemRewards;
    std::unordered_map<uint8, uint32> hardcoreTalentRewards, semiHardcoreTalentRewards, selfCraftedTalentRewards, itemQualityLevelTalentRewards, slowXpGainTalentRewards, verySlowXpGainTalentRewards, turtleModeXpGainTalentRewards, questXpOnlyTalentRewards, ironManTalentRewards, pacifistTalentRewards, questlessTalentRewards, cashlessTalentRewards;
    std::unordered_map<uint8, uint32> hardcoreAchievementReward, semiHardcoreAchievementReward, selfCraftedAchievementReward, itemQualityLevelAchievementReward, slowXpGainAchievementReward, verySlowXpGainAchievementReward, turtleModeXpGainAchievementReward, questXpOnlyAchievementReward, ironManAchievementReward, pacifistAchievementReward, questlessAchievementReward, cashlessAchievementReward;

    std::unordered_map<std::string, std::unordered_map<uint8, uint32>*> rewardConfigMap =
    {
        { "Hardcore.TitleRewards",                &hardcoreTitleRewards                 },
        { "SemiHardcore.TitleRewards",            &semiHardcoreTitleRewards             },
        { "SelfCrafted.TitleRewards",             &selfCraftedTitleRewards              },
        { "ItemQualityLevel.TitleRewards",        &itemQualityLevelTitleRewards         },
        { "SlowXpGain.TitleRewards",              &slowXpGainTitleRewards               },
        { "VerySlowXpGain.TitleRewards",          &verySlowXpGainTitleRewards           },
        { "QuestXpOnly.TitleRewards",             &questXpOnlyTitleRewards              },
        { "IronMan.TitleRewards",                 &ironManTitleRewards                  },
        { "Pacifist.TitleRewards",                &pacifistTitleRewards                 }, 
        { "TurtleMode.TitleRewards",              &turtleModeXpGainTitleRewards         },
        { "Questless.TitleRewards",               &questlessTitleRewards                },
        { "Cashless.TitleRewards",                &cashlessTitleRewards                 },

        { "Hardcore.TalentRewards",               &hardcoreTalentRewards                },
        { "SemiHardcore.TalentRewards",           &semiHardcoreTalentRewards            },
        { "SelfCrafted.TalentRewards",            &selfCraftedTalentRewards             },
        { "ItemQualityLevel.TalentRewards",       &itemQualityLevelTalentRewards        },
        { "SlowXpGain.TalentRewards",             &slowXpGainTalentRewards              },
        { "VerySlowXpGain.TalentRewards",         &verySlowXpGainTalentRewards          },
        { "QuestXpOnly.TalentRewards",            &questXpOnlyTalentRewards             },
        { "IronMan.TalentRewards",                &ironManTalentRewards                 },
        { "Pacifist.TalentRewards",               &pacifistTalentRewards                },
        { "TurtleMode.TalentRewards",             &turtleModeXpGainTalentRewards        },
        { "Questless.TalentRewards",              &questlessTalentRewards               },
        { "Cashless.TalentRewards",               &cashlessTalentRewards                },

        { "Hardcore.ItemRewards",                 &hardcoreItemRewards                  },
        { "SemiHardcore.ItemRewards",             &semiHardcoreItemRewards              },
        { "SelfCrafted.ItemRewards",              &selfCraftedItemRewards               }, 
        { "ItemQualityLevel.ItemRewards",         &itemQualityLevelItemRewards          },
        { "SlowXpGain.ItemRewards",               &slowXpGainItemRewards                },
        { "VerySlowXpGain.ItemRewards",           &verySlowXpGainItemRewards            },
        { "QuestXpOnly.ItemRewards",              &questXpOnlyItemRewards               },
        { "IronMan.ItemRewards",                  &ironManItemRewards                   },
        { "Pacifist.ItemRewards",                 &pacifistItemRewards                  }, 
        { "TurtleMode.ItemRewards",               &turtleModeXpGainItemRewards          },
        { "Questless.ItemRewards",                &questlessItemRewards                 },
        { "Cashless.ItemRewards",                 &cashlessItemRewards                  },

        { "Hardcore.AchievementReward",           &hardcoreAchievementReward            },
        { "SemiHardcore.AchievementReward",       &semiHardcoreAchievementReward        },
        { "SelfCrafted.AchievementReward",        &selfCraftedAchievementReward         },
        { "ItemQualityLevel.AchievementReward",   &itemQualityLevelAchievementReward    },
        { "SlowXpGain.AchievementReward",         &slowXpGainAchievementReward          },
        { "VerySlowXpGain.AchievementReward",     &verySlowXpGainAchievementReward      },
        { "QuestXpOnly.AchievementReward",        &questXpOnlyAchievementReward         },
        { "IronMan.AchievementReward",            &ironManAchievementReward             },
        { "Pacifist.AchievementReward",           &pacifistAchievementReward            },
        { "TurtleMode.AchievementReward",         &turtleModeXpGainAchievementReward    },
        { "Questless.AchievementReward",          &questlessAchievementReward           },
        { "Cashless.AchievementReward",           &cashlessAchievementReward            }
    };

    [[nodiscard]] bool enabled() const { return challengesEnabled; }
    [[nodiscard]] bool challengeEnabled(ChallengeModeSettings setting) const;
    [[nodiscard]] uint32 getDisableLevel(ChallengeModeSettings setting) const;
    [[nodiscard]] float getXpBonusForChallenge(ChallengeModeSettings setting) const;
    bool challengeEnabledForPlayer(ChallengeModeSettings setting, Player* player) const;
    [[nodiscard]] const std::unordered_map<uint8, uint32> *getTitleMapForChallenge(ChallengeModeSettings setting) const;
    [[nodiscard]] const std::unordered_map<uint8, uint32> *getTalentMapForChallenge(ChallengeModeSettings setting) const;
    [[nodiscard]] const std::unordered_map<uint8, uint32> *getItemMapForChallenge(ChallengeModeSettings setting) const;
    [[nodiscard]] const std::unordered_map<uint8, uint32> *getAchievementMapForChallenge(ChallengeModeSettings setting) const;
    [[nodiscard]] uint32 getItemRewardAmount(ChallengeModeSettings setting) const;
    void LearnSpellsForNewLevel(Player* player, uint8 fromLevel);
};

#define sChallengeModes ChallengeModes::instance()

#endif //AZEROTHCORE_CHALLENGEMODES_H
