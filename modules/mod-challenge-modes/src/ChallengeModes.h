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
    SETTING_CASHLESS           = 12,
    SETTING_BOAR_ONLY          = 13,
    SETTING_REPAIRLESS         = 14,
    SETTING_SELFMADE           = 15
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
    ChallengeModes();
    void InitializeAdditionalSpells();

    bool challengesEnabled, hardcoreEnable, semiHardcoreEnable, selfCraftedEnable, itemQualityLevelEnable, slowXpGainEnable, verySlowXpGainEnable, turtleModeEnable, questXpOnlyEnable, ironManEnable, pacifistEnable, questlessEnable, cashlessEnable, boarEnable, repairEnable, selfmadeEnable;
    uint32 hardcoreDisableLevel, semiHardcoreDisableLevel, selfCraftedDisableLevel, itemQualityLevelDisableLevel, slowXpGainDisableLevel, verySlowXpGainDisableLevel, turtleModeDisableLevel, questXpOnlyDisableLevel, ironManDisableLevel, pacifistDisableLevel, questlessDisableLevel, cashlessDisableLevel, boarDisableLevel, repairDisableLevel, selfmadeDisableLevel;
    uint32 hardcoreItemRewardAmount, semiHardcoreItemRewardAmount, selfCraftedItemRewardAmount, itemQualityLevelItemRewardAmount, slowXpGainItemRewardAmount, verySlowXpGainItemRewardAmount, turtleModeXpGainItemRewardAmount, questXpOnlyItemRewardAmount, ironManItemRewardAmount, pacifistItemRewardAmount, questlessItemRewardAmount, cashlessItemRewardAmount, boarItemRewardAmount, repairItemRewardAmount, selfmadeItemRewardAmount;
    float hardcoreXpBonus, semiHardcoreXpBonus, selfCraftedXpBonus, itemQualityLevelXpBonus, questXpOnlyXpBonus, slowXpGainBonus, verySlowXpGainBonus, turtleModeXpGainBonus, ironManXpBonus, pacifistXpBonus, questlessXpBonus, cashlessXpBonus, boarXpBonus, repairXpBonus, selfmadeXpBonus;

    std::unordered_map<uint8, uint32> hardcoreTitleRewards, semiHardcoreTitleRewards, selfCraftedTitleRewards, itemQualityLevelTitleRewards, slowXpGainTitleRewards, verySlowXpGainTitleRewards, turtleModeXpGainTitleRewards, questXpOnlyTitleRewards, ironManTitleRewards, pacifistTitleRewards, questlessTitleRewards, cashlessTitleRewards, boarTitleRewards, repairTitleRewards, selfmadeTitleRewards;
    std::unordered_map<uint8, uint32> hardcoreItemRewards, semiHardcoreItemRewards, selfCraftedItemRewards, itemQualityLevelItemRewards, slowXpGainItemRewards, verySlowXpGainItemRewards, turtleModeXpGainItemRewards, questXpOnlyItemRewards, ironManItemRewards, pacifistItemRewards, questlessItemRewards, cashlessItemRewards, boarItemRewards, repairItemRewards, selfmadeItemRewards;
    std::unordered_map<uint8, uint32> hardcoreTalentRewards, semiHardcoreTalentRewards, selfCraftedTalentRewards, itemQualityLevelTalentRewards, slowXpGainTalentRewards, verySlowXpGainTalentRewards, turtleModeXpGainTalentRewards, questXpOnlyTalentRewards, ironManTalentRewards, pacifistTalentRewards, questlessTalentRewards, cashlessTalentRewards, boarTalentRewards, repairTalentRewards, selfmadeTalentRewards;
    std::unordered_map<uint8, uint32> hardcoreAchievementReward, semiHardcoreAchievementReward, selfCraftedAchievementReward, itemQualityLevelAchievementReward, slowXpGainAchievementReward, verySlowXpGainAchievementReward, turtleModeXpGainAchievementReward, questXpOnlyAchievementReward, ironManAchievementReward, pacifistAchievementReward, questlessAchievementReward, cashlessAchievementReward, boarAchievementReward, repairAchievementReward, selfmadeAchievementReward;

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
        { "BoarOnly.TitleRewards",                &boarTitleRewards                     },
        { "Repairless.TitleRewards",              &repairTitleRewards                   },
        { "SelfMade.TitleRewards",                &selfmadeTitleRewards                 },

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
        { "BoarOnly.TalentRewards",               &boarTalentRewards                    },
        { "Repairless.TalentRewards",             &repairTalentRewards                  },
        { "SelfMade.TalentRewards",               &selfmadeTalentRewards                },

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
        { "BoarOnly.ItemRewards",                 &boarItemRewards                      },
        { "Repairless.ItemRewards",               &repairItemRewards                    },
        { "SelfMade.ItemRewards",                 &selfmadeItemRewards                  },

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
        { "Cashless.AchievementReward",           &cashlessAchievementReward            },
        { "BoarOnly.AchievementReward",           &boarAchievementReward                },
        { "Repairless.AchievementReward",         &repairAchievementReward              },
        { "SelfMade.AchievementReward",           &selfmadeAchievementReward            }

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
    uint32 GetSpellFamily(const Player* p);
    void ApplyAdditionalSpells(uint8 level, uint32 playerSpellFamily, Player* player);
    bool IsIgnoredSpell(uint32 spellID);
};

#define sChallengeModes ChallengeModes::instance()

#endif //CHALLENGEMODES_H
