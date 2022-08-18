/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"
#include "Config.h"
#include "TaskScheduler.h"
#include "WarEffort.h"

WarEffort* WarEffort::instance()
{
    static WarEffort instance;
    return &instance;
}

void WarEffort::SaveData()
{
    CharacterDatabase.Query("UPDATE wareffort SET "
                            "bandages01 = {}, bandages02 = {}, bandages03 = {},"
                            "food01 = {}, food02 = {}, food03 = {},"
                            "herbs01 = {}, herbs02 = {}, herbs03 = {},"
                            "metals01 = {}, metals02 = {}, metals03 = {},"
                            "leather01 = {}, leather02 = {}, leather03 = {} "
                            "WHERE id = {} AND faction = {}",
        sWarEffort->materialsHorde[MATERIAL_WOOL], sWarEffort->materialsHorde[MATERIAL_MAGEWEAVE], sWarEffort->materialsHorde[MATERIAL_RUNECLOTH_B],
        sWarEffort->materialsHorde[MATERIAL_WOLF], sWarEffort->materialsHorde[MATERIAL_SALMON], sWarEffort->materialsHorde[MATERIAL_YELLOWTAIL_H],
        sWarEffort->materialsHorde[MATERIAL_PEACEBLOOM], sWarEffort->materialsHorde[MATERIAL_FIREBLOOM], sWarEffort->materialsHorde[MATERIAL_PURPLE_LOTUS_H],
        sWarEffort->materialsHorde[MATERIAL_TIN], sWarEffort->materialsHorde[MATERIAL_MITHRIL], sWarEffort->materialsHorde[MATERIAL_COOPER_H],
        sWarEffort->materialsHorde[MATERIAL_HEAVY_LEATHER], sWarEffort->materialsHorde[MATERIAL_RUGGER_LEATHER], sWarEffort->materialsHorde[MATERIAL_THICK_LEATHER_B],
        sConfigMgr->GetOption<uint32>("ModWarEffort.Id", 1), TEAM_HORDE
    );

    CharacterDatabase.Query("UPDATE wareffort SET "
                            "bandages01 = {}, bandages02 = {}, bandages03 = {},"
                            "food01 = {}, food02 = {}, food03 = {},"
                            "herbs01 = {}, herbs02 = {}, herbs03 = {},"
                            "metals01 = {}, metals02 = {}, metals03 = {},"
                            "leather01 = {}, leather02 = {}, leather03 = {} "
                            "WHERE id = {} AND faction = {}",
        sWarEffort->materialsAlliance[MATERIAL_LINEN], sWarEffort->materialsAlliance[MATERIAL_SILK], sWarEffort->materialsAlliance[MATERIAL_RUNECLOTH_A],
        sWarEffort->materialsAlliance[MATERIAL_ALBACORE], sWarEffort->materialsAlliance[MATERIAL_RAPTOR], sWarEffort->materialsAlliance[MATERIAL_YELLOWTAIL_A],
        sWarEffort->materialsAlliance[MATERIAL_STRANGLEKELP], sWarEffort->materialsAlliance[MATERIAL_ARTHAS_TEARS], sWarEffort->materialsAlliance[MATERIAL_PURPLE_LOTUS_A],
        sWarEffort->materialsAlliance[MATERIAL_IRON], sWarEffort->materialsAlliance[MATERIAL_THORIUM], sWarEffort->materialsAlliance[MATERIAL_COOPER_A],
        sWarEffort->materialsAlliance[MATERIAL_LIGHT_LEATHER], sWarEffort->materialsAlliance[MATERIAL_MEDIUM_LEATHER], sWarEffort->materialsAlliance[MATERIAL_THICK_LEATHER_A],
        sConfigMgr->GetOption<uint32>("ModWarEffort.Id", 1), TEAM_ALLIANCE
    );
}

void WarEffort::LoadData()
{
    if (QueryResult result = CharacterDatabase.Query("SELECT * FROM Wareffort WHERE id = {}", sWarEffort->GetActiveEventId()))
    {
        do
        {
            if ((*result)[1].Get<uint32>() == TEAM_ALLIANCE)
            {
                sWarEffort->materialsAlliance[MATERIAL_LINEN] = (*result)[2].Get<uint32>();
                sWarEffort->materialsAlliance[MATERIAL_SILK] = (*result)[3].Get<uint32>();
                sWarEffort->materialsAlliance[MATERIAL_RUNECLOTH_A] = (*result)[4].Get<uint32>();
                sWarEffort->materialsAlliance[MATERIAL_ALBACORE] = (*result)[5].Get<uint32>();
                sWarEffort->materialsAlliance[MATERIAL_RAPTOR] = (*result)[6].Get<uint32>();
                sWarEffort->materialsAlliance[MATERIAL_YELLOWTAIL_A] = (*result)[7].Get<uint32>();
                sWarEffort->materialsAlliance[MATERIAL_STRANGLEKELP] = (*result)[8].Get<uint32>();
                sWarEffort->materialsAlliance[MATERIAL_ARTHAS_TEARS] = (*result)[9].Get<uint32>();
                sWarEffort->materialsAlliance[MATERIAL_PURPLE_LOTUS_A] = (*result)[10].Get<uint32>();
                sWarEffort->materialsAlliance[MATERIAL_IRON] = (*result)[11].Get<uint32>();
                sWarEffort->materialsAlliance[MATERIAL_THORIUM] = (*result)[12].Get<uint32>();
                sWarEffort->materialsAlliance[MATERIAL_COOPER_A] = (*result)[13].Get<uint32>();
                sWarEffort->materialsAlliance[MATERIAL_LIGHT_LEATHER] = (*result)[14].Get<uint32>();
                sWarEffort->materialsAlliance[MATERIAL_MEDIUM_LEATHER] = (*result)[15].Get<uint32>();
                sWarEffort->materialsAlliance[MATERIAL_THICK_LEATHER_A] = (*result)[16].Get<uint32>();
            }
            else
            {
                sWarEffort->materialsHorde[MATERIAL_WOOL] = (*result)[2].Get<uint32>();
                sWarEffort->materialsHorde[MATERIAL_MAGEWEAVE] = (*result)[3].Get<uint32>();
                sWarEffort->materialsHorde[MATERIAL_RUNECLOTH_B] = (*result)[4].Get<uint32>();
                sWarEffort->materialsHorde[MATERIAL_WOLF] = (*result)[5].Get<uint32>();
                sWarEffort->materialsHorde[MATERIAL_SALMON] = (*result)[6].Get<uint32>();
                sWarEffort->materialsHorde[MATERIAL_YELLOWTAIL_H] = (*result)[7].Get<uint32>();
                sWarEffort->materialsHorde[MATERIAL_PEACEBLOOM] = (*result)[8].Get<uint32>();
                sWarEffort->materialsHorde[MATERIAL_FIREBLOOM] = (*result)[9].Get<uint32>();
                sWarEffort->materialsHorde[MATERIAL_PURPLE_LOTUS_H] = (*result)[10].Get<uint32>();
                sWarEffort->materialsHorde[MATERIAL_TIN] = (*result)[11].Get<uint32>();
                sWarEffort->materialsHorde[MATERIAL_MITHRIL] = (*result)[12].Get<uint32>();
                sWarEffort->materialsHorde[MATERIAL_COOPER_H] = (*result)[13].Get<uint32>();
                sWarEffort->materialsHorde[MATERIAL_HEAVY_LEATHER] = (*result)[14].Get<uint32>();
                sWarEffort->materialsHorde[MATERIAL_RUGGER_LEATHER] = (*result)[15].Get<uint32>();
                sWarEffort->materialsHorde[MATERIAL_THICK_LEATHER_B] = (*result)[16].Get<uint32>();
            }
        } while (result->NextRow());
    }
};

bool WarEffort::IsBellowPercentGathered(uint8 material, uint8 team, int pct)
{
    auto materials = team == TEAM_ALLIANCE ? sWarEffort->materialsAlliance : sWarEffort->materialsHorde;

    switch (material)
    {
        case MATERIAL_CAT_BANDAGES:
            for (uint8 i = 0; i >= 3; ++i)
            {
                if (team == TEAM_ALLIANCE)
                {
                    if ((materials[i] * pct) < (WarEffortMaterialsAlliance[i].Goal * pct))
                    {
                        return true;
                    }
                }
                else
                {
                    if ((materials[i] * pct) < (WarEffortMaterialsHorde[i].Goal * pct))
                    {
                        return true;
                    }
                }

            }
            break;
        case MATERIAL_CAT_FOOD:
            for (uint8 i = 3; i >= 6; ++i)
            {
                if (team == TEAM_ALLIANCE)
                {
                    if ((materials[i] * pct) < (WarEffortMaterialsAlliance[i].Goal * pct))
                    {
                        return true;
                    }
                }
                else
                {
                    if ((materials[i] * pct) < (WarEffortMaterialsHorde[i].Goal * pct))
                    {
                        return true;
                    }
                }

            }
            break;
        case MATERIAL_CAT_HERBS:
            for (uint8 i = 6; i >= 9; ++i)
            {
                if (team == TEAM_ALLIANCE)
                {
                    if ((materials[i] * pct) < (WarEffortMaterialsAlliance[i].Goal * pct))
                    {
                        return true;
                    }
                }
                else
                {
                    if ((materials[i] * pct) < (WarEffortMaterialsHorde[i].Goal * pct))
                    {
                        return true;
                    }
                }

            }
            break;
        case MATERIAL_CAT_METAL:
            for (uint8 i = 9; i >= 12; ++i)
            {
                if (team == TEAM_ALLIANCE)
                {
                    if ((materials[i] * pct) < (WarEffortMaterialsAlliance[i].Goal * pct))
                    {
                        return true;
                    }
                }
                else if ((materials[i] * pct) < (WarEffortMaterialsHorde[i].Goal * pct))
                {
                    return true;
                }

            }
            break;
        case MATERIAL_CAT_LEATHER:
            for (uint8 i = 12; i >= 15; ++i)
            {
                if (team == TEAM_ALLIANCE)
                {
                    if ((materials[i] * pct) < (WarEffortMaterialsAlliance[i].Goal * pct))
                    {
                        return true;
                    }
                }
                else if ((materials[i] * pct) < (WarEffortMaterialsHorde[i].Goal * pct))
                {
                    return true;
                }

            }
            break;

    }

    return false;
}

void WarEffort::RemoveNearbyObject(uint32 entry, Unit* unit)
{
    if (GameObject* go = unit->FindNearestGameObject(entry, 50.0f))
    {
        go->Delete();
    }
}

void WarEffort::CheckGoal(Unit* unit, uint8 material, uint8 team)
{
    // @todo: This whole thing probably could be done better, but no time to find a better design right now.

    uint32 goal = team == TEAM_ALLIANCE ? WarEffortMaterialsAlliance[material].Goal : WarEffortMaterialsHorde[material].Goal;

    switch (material)
    {
        // Bandages
        case MATERIAL_CAT_BANDAGES:
        {
            if (team == TEAM_ALLIANCE)
            {
                if (sWarEffort->IsBellowPercentGathered(material, team, 0.20f))
                {
                    //
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.20f) && sWarEffort->IsBellowPercentGathered(material, team, 0.40f))
                {
                    if (!unit->FindNearestGameObject(GO_BANDAGES_ALLIANCE_TIER_1, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_BANDAGES_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_BANDAGES_ALLIANCE_TIER_1, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, -0.886385f, -0.462949f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.40f) && sWarEffort->IsBellowPercentGathered(material, team, 0.60f))
                {
                    sWarEffort->RemoveNearbyObject(GO_BANDAGES_ALLIANCE_TIER_1, unit);

                    if (!unit->FindNearestGameObject(GO_BANDAGES_ALLIANCE_TIER_2, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_BANDAGES_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_BANDAGES_ALLIANCE_TIER_2, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, -0.886385f, -0.462949f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.60f) && sWarEffort->IsBellowPercentGathered(material, team, 0.80))
                {
                    sWarEffort->RemoveNearbyObject(GO_BANDAGES_ALLIANCE_TIER_2, unit);

                    if (!unit->FindNearestGameObject(GO_BANDAGES_ALLIANCE_TIER_3, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_BANDAGES_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_BANDAGES_ALLIANCE_TIER_3, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, -0.886385f, -0.462949f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.80) && sWarEffort->IsBellowPercentGathered(material, team, 1.0f))
                {
                    sWarEffort->RemoveNearbyObject(GO_BANDAGES_ALLIANCE_TIER_3, unit);

                    if (!unit->FindNearestGameObject(GO_BANDAGES_ALLIANCE_TIER_4, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_BANDAGES_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_BANDAGES_ALLIANCE_TIER_4, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, -0.886385f, -0.462949f, 14 * DAY * MINUTE);
                    }
                }
                else
                {
                    sWarEffort->RemoveNearbyObject(GO_BANDAGES_ALLIANCE_TIER_4, unit);

                    if (!unit->FindNearestGameObject(GO_BANDAGES_ALLIANCE_TIER_5, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_BANDAGES_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_BANDAGES_ALLIANCE_TIER_5, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, -0.886385f, -0.462949f, 14 * DAY * MINUTE);
                    }
                }
            }
            else
            {
                if (sWarEffort->IsBellowPercentGathered(material, team, 0.20f))
                {
                    if (!unit->FindNearestGameObject(GO_BANDAGES_HORDE_INITIAL, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_BANDAGES_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_BANDAGES_HORDE_INITIAL, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.20f) && sWarEffort->IsBellowPercentGathered(material, team, 0.40f))
                {
                    sWarEffort->RemoveNearbyObject(GO_BANDAGES_HORDE_INITIAL, unit);

                    if (!unit->FindNearestGameObject(GO_BANDAGES_HORDE_TIER_1, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_BANDAGES_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_BANDAGES_HORDE_TIER_1, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ() + 0.7f, pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.40f) && sWarEffort->IsBellowPercentGathered(material, team, 0.60f))
                {
                    sWarEffort->RemoveNearbyObject(GO_BANDAGES_HORDE_TIER_1, unit);

                    if (!unit->FindNearestGameObject(GO_BANDAGES_HORDE_TIER_2, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_BANDAGES_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_BANDAGES_HORDE_TIER_2, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.60f) && sWarEffort->IsBellowPercentGathered(material, team, 0.80))
                {
                    sWarEffort->RemoveNearbyObject(GO_BANDAGES_HORDE_TIER_2, unit);

                    if (!unit->FindNearestGameObject(GO_BANDAGES_HORDE_TIER_3, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_BANDAGES_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_BANDAGES_HORDE_TIER_3, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.80) && sWarEffort->IsBellowPercentGathered(material, team, 1.0f))
                {
                    sWarEffort->RemoveNearbyObject(GO_BANDAGES_HORDE_TIER_3, unit);

                    if (!unit->FindNearestGameObject(GO_BANDAGES_HORDE_TIER_4, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_BANDAGES_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_BANDAGES_HORDE_TIER_4, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else
                {
                    sWarEffort->RemoveNearbyObject(GO_BANDAGES_HORDE_TIER_4, unit);

                    if (!unit->FindNearestGameObject(GO_BANDAGES_HORDE_TIER_5, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_BANDAGES_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_BANDAGES_HORDE_TIER_5, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 0);
                    }
                }
            }

            break;
        }
        // Food
        case MATERIAL_CAT_FOOD:
            if (team == TEAM_ALLIANCE)
            {
                if (sWarEffort->IsBellowPercentGathered(material, team, 0.20f))
                {
                    //
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.20f) && sWarEffort->IsBellowPercentGathered(material, team, 0.40f))
                {
                    if (!unit->FindNearestGameObject(GO_FOOD_ALLIANCE_TIER_1, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_FOOD_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_FOOD_ALLIANCE_TIER_1, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, -0.496055f, -0.868291f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.40f) && sWarEffort->IsBellowPercentGathered(material, team, 0.60f))
                {
                    sWarEffort->RemoveNearbyObject(GO_FOOD_ALLIANCE_TIER_1, unit);

                    if (!unit->FindNearestGameObject(GO_FOOD_ALLIANCE_TIER_2, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_FOOD_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_FOOD_ALLIANCE_TIER_2, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, -0.496055f, -0.868291f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.60f) && sWarEffort->IsBellowPercentGathered(material, team, 0.80))
                {
                    sWarEffort->RemoveNearbyObject(GO_FOOD_ALLIANCE_TIER_2, unit);

                    if (!unit->FindNearestGameObject(GO_FOOD_ALLIANCE_TIER_3, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_FOOD_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_FOOD_ALLIANCE_TIER_3, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, -0.496055f, -0.868291f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.80) && sWarEffort->IsBellowPercentGathered(material, team, 1.0f))
                {
                    sWarEffort->RemoveNearbyObject(GO_FOOD_ALLIANCE_TIER_3, unit);

                    if (!unit->FindNearestGameObject(GO_FOOD_ALLIANCE_TIER_4, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_FOOD_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_FOOD_ALLIANCE_TIER_4, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, -0.496055f, -0.868291f, 14 * DAY * MINUTE);
                    }
                }
                else
                {
                    sWarEffort->RemoveNearbyObject(GO_FOOD_ALLIANCE_TIER_4, unit);

                    if (!unit->FindNearestGameObject(GO_FOOD_ALLIANCE_TIER_5, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_FOOD_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_FOOD_ALLIANCE_TIER_5, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, -0.496055f, -0.868291f, 14 * DAY * MINUTE);
                    }
                }
            }
            else
            {
                if (sWarEffort->IsBellowPercentGathered(material, team, 0.20f))
                {
                    if (!unit->FindNearestGameObject(GO_FOOD_HORDE_INITIAL, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_FOOD_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_FOOD_HORDE_INITIAL, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ() + 0.5f, pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.20f) && sWarEffort->IsBellowPercentGathered(material, team, 0.40f))
                {
                    sWarEffort->RemoveNearbyObject(GO_FOOD_HORDE_INITIAL, unit);

                    if (!unit->FindNearestGameObject(GO_FOOD_HORDE_TIER_1, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_BANDAGES_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_FOOD_HORDE_TIER_1, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ() + 0.7f, pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.40f) && sWarEffort->IsBellowPercentGathered(material, team, 0.60f))
                {
                    sWarEffort->RemoveNearbyObject(GO_FOOD_HORDE_TIER_1, unit);

                    if (!unit->FindNearestGameObject(GO_FOOD_HORDE_TIER_2, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_FOOD_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_FOOD_HORDE_TIER_2, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ() + 0.7f, pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.60f) && sWarEffort->IsBellowPercentGathered(material, team, 0.80))
                {
                    sWarEffort->RemoveNearbyObject(GO_FOOD_HORDE_TIER_2, unit);

                    if (!unit->FindNearestGameObject(GO_FOOD_HORDE_TIER_3, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_FOOD_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_FOOD_HORDE_TIER_3, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ() + 0.7f, pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.80) && sWarEffort->IsBellowPercentGathered(material, team, 1.0f))
                {
                    sWarEffort->RemoveNearbyObject(GO_FOOD_HORDE_TIER_3, unit);

                    if (!unit->FindNearestGameObject(GO_FOOD_HORDE_TIER_4, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_FOOD_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_FOOD_HORDE_TIER_4, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ() + 0.7f, pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else
                {
                    sWarEffort->RemoveNearbyObject(GO_FOOD_HORDE_TIER_4, unit);

                    if (!unit->FindNearestGameObject(GO_FOOD_HORDE_TIER_5, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_FOOD_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_FOOD_HORDE_TIER_5, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ() + 0.7f, pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
            }
            break;
        // Herbs
        case MATERIAL_CAT_HERBS:
            if (team == TEAM_ALLIANCE)
            {
                if (sWarEffort->IsBellowPercentGathered(material, team, 0.20f))
                {
                    // Already spawned by default
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.20f) && sWarEffort->IsBellowPercentGathered(material, team, 0.40f))
                {
                    if (!unit->FindNearestGameObject(GO_HERBS_ALLIANCE_TIER_1, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_HERBS_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_HERBS_ALLIANCE_TIER_1, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, -0.522955f, -0.85236f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.40f) && sWarEffort->IsBellowPercentGathered(material, team, 0.60f))
                {
                    sWarEffort->RemoveNearbyObject(GO_HERBS_ALLIANCE_TIER_1, unit);

                    if (!unit->FindNearestGameObject(GO_HERBS_ALLIANCE_TIER_2, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_HERBS_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_HERBS_ALLIANCE_TIER_2, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, -0.522955f, -0.85236f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.60f) && sWarEffort->IsBellowPercentGathered(material, team, 0.80))
                {
                    sWarEffort->RemoveNearbyObject(GO_HERBS_ALLIANCE_TIER_2, unit);

                    if (!unit->FindNearestGameObject(GO_HERBS_ALLIANCE_TIER_3, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_HERBS_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_HERBS_ALLIANCE_TIER_3, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, -0.522955f, -0.85236f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.80f) && sWarEffort->IsBellowPercentGathered(material, team, 1.0f))
                {
                    sWarEffort->RemoveNearbyObject(GO_HERBS_ALLIANCE_TIER_3, unit);

                    if (!unit->FindNearestGameObject(GO_HERBS_ALLIANCE_TIER_4, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_HERBS_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_HERBS_ALLIANCE_TIER_4, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, -0.522955f, -0.85236f, 14 * DAY * MINUTE);
                    }
                }
                else
                {
                    sWarEffort->RemoveNearbyObject(GO_HERBS_ALLIANCE_TIER_4, unit);

                    if (!unit->FindNearestGameObject(GO_HERBS_ALLIANCE_TIER_5, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_HERBS_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_HERBS_ALLIANCE_TIER_5, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, -0.522955f, -0.85236f, 14 * DAY * MINUTE);
                    }
                }
            }
            else
            {
                if (sWarEffort->IsBellowPercentGathered(material, team, 0.20f))
                {
                    if (!unit->FindNearestGameObject(GO_HERBS_HORDE_INITIAL, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_HERBS_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_HERBS_HORDE_INITIAL, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.20f) && sWarEffort->IsBellowPercentGathered(material, team, 0.40f))
                {
                    sWarEffort->RemoveNearbyObject(GO_HERBS_HORDE_INITIAL, unit);

                    if (!unit->FindNearestGameObject(GO_HERBS_HORDE_TIER_1, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_HERBS_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_HERBS_HORDE_TIER_1, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.40f) && sWarEffort->IsBellowPercentGathered(material, team, 0.60f))
                {
                    sWarEffort->RemoveNearbyObject(GO_HERBS_HORDE_TIER_1, unit);

                    if (!unit->FindNearestGameObject(GO_HERBS_HORDE_TIER_2, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_HERBS_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_HERBS_HORDE_TIER_2, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.60f) && sWarEffort->IsBellowPercentGathered(material, team, 0.80))
                {
                    sWarEffort->RemoveNearbyObject(GO_HERBS_HORDE_TIER_2, unit);

                    if (!unit->FindNearestGameObject(GO_HERBS_HORDE_TIER_3, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_HERBS_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_HERBS_HORDE_TIER_3, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.80) && sWarEffort->IsBellowPercentGathered(material, team, 1.0f))
                {
                    sWarEffort->RemoveNearbyObject(GO_HERBS_HORDE_TIER_3, unit);

                    if (!unit->FindNearestGameObject(GO_HERBS_HORDE_TIER_4, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_HERBS_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_HERBS_HORDE_TIER_4, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else
                {
                    sWarEffort->RemoveNearbyObject(GO_HERBS_HORDE_TIER_4, unit);

                    if (!unit->FindNearestGameObject(GO_HERBS_HORDE_TIER_5, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_HERBS_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_HERBS_HORDE_TIER_5, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
            }
            break;
        // Meetal
        case MATERIAL_CAT_METAL:
            if (team == TEAM_ALLIANCE)
            {
                if (sWarEffort->IsBellowPercentGathered(material, team, 0.20f))
                {
                    //
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.20f) && sWarEffort->IsBellowPercentGathered(material, team, 0.40f))
                {
                    if (!unit->FindNearestGameObject(GO_METAL_ALLIANCE_TIER_1, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_METAL_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_METAL_ALLIANCE_TIER_1, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, -0.522955f, -0.85236f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.40f) && sWarEffort->IsBellowPercentGathered(material, team, 0.60f))
                {
                    sWarEffort->RemoveNearbyObject(GO_METAL_ALLIANCE_TIER_1, unit);

                    if (!unit->FindNearestGameObject(GO_METAL_ALLIANCE_TIER_2, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_METAL_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_METAL_ALLIANCE_TIER_2, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.60f) && sWarEffort->IsBellowPercentGathered(material, team, 0.80))
                {
                    sWarEffort->RemoveNearbyObject(GO_METAL_ALLIANCE_TIER_2, unit);

                    if (!unit->FindNearestGameObject(GO_METAL_ALLIANCE_TIER_3, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_METAL_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_METAL_ALLIANCE_TIER_3, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.80f) && sWarEffort->IsBellowPercentGathered(material, team, 1.0f))
                {
                    sWarEffort->RemoveNearbyObject(GO_METAL_ALLIANCE_TIER_3, unit);

                    if (!unit->FindNearestGameObject(GO_METAL_ALLIANCE_TIER_4, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_METAL_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_METAL_ALLIANCE_TIER_4, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else
                {
                    sWarEffort->RemoveNearbyObject(GO_METAL_ALLIANCE_TIER_4, unit);

                    if (!unit->FindNearestGameObject(GO_METAL_ALLIANCE_TIER_5, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_METAL_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_METAL_ALLIANCE_TIER_5, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
            }
            else
            {
                if (sWarEffort->IsBellowPercentGathered(material, team, 0.20f))
                {
                    if (!unit->FindNearestGameObject(GO_METAL_HORDE_INITIAL, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_METAL_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_METAL_HORDE_INITIAL, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), -0.0f, -0.0f, -0.987771f, 0.155913f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.20f) && sWarEffort->IsBellowPercentGathered(material, team, 0.40f))
                {
                    sWarEffort->RemoveNearbyObject(GO_METAL_HORDE_INITIAL, unit);

                    if (!unit->FindNearestGameObject(GO_METAL_HORDE_TIER_1, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_HERBS_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_METAL_HORDE_TIER_1, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.40f) && sWarEffort->IsBellowPercentGathered(material, team, 0.60f))
                {
                    sWarEffort->RemoveNearbyObject(GO_METAL_HORDE_TIER_1, unit);

                    if (!unit->FindNearestGameObject(GO_METAL_HORDE_TIER_2, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_HERBS_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_METAL_HORDE_TIER_2, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.60f) && sWarEffort->IsBellowPercentGathered(material, team, 0.80))
                {
                    sWarEffort->RemoveNearbyObject(GO_METAL_HORDE_TIER_2, unit);

                    if (!unit->FindNearestGameObject(GO_METAL_HORDE_TIER_3, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_HERBS_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_METAL_HORDE_TIER_3, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.80) && sWarEffort->IsBellowPercentGathered(material, team, 1.0f))
                {
                    sWarEffort->RemoveNearbyObject(GO_METAL_HORDE_TIER_3, unit);

                    if (!unit->FindNearestGameObject(GO_METAL_HORDE_TIER_4, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_HERBS_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_METAL_HORDE_TIER_4, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else
                {
                    sWarEffort->RemoveNearbyObject(GO_METAL_HORDE_TIER_4, unit);

                    if (!unit->FindNearestGameObject(GO_METAL_HORDE_TIER_5, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_HERBS_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_METAL_HORDE_TIER_5, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
            }
            break;
        // Leather
        case MATERIAL_CAT_LEATHER:
            if (team == TEAM_ALLIANCE)
            {
                if (sWarEffort->IsBellowPercentGathered(material, team, 0.20f))
                {
                    // Already spawned
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.20f) && sWarEffort->IsBellowPercentGathered(material, team, 0.40f))
                {
                    if (!unit->FindNearestGameObject(GO_LEATHER_ALLIANCE_TIER_1, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_LEATHER_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_LEATHER_ALLIANCE_TIER_1, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, -0.788872f, -0.614557f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.40f) && sWarEffort->IsBellowPercentGathered(material, team, 0.60f))
                {
                    sWarEffort->RemoveNearbyObject(GO_LEATHER_ALLIANCE_TIER_1, unit);

                    if (!unit->FindNearestGameObject(GO_LEATHER_ALLIANCE_TIER_2, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_LEATHER_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_LEATHER_ALLIANCE_TIER_2, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.60f) && sWarEffort->IsBellowPercentGathered(material, team, 0.80))
                {
                    sWarEffort->RemoveNearbyObject(GO_LEATHER_ALLIANCE_TIER_2, unit);

                    if (!unit->FindNearestGameObject(GO_LEATHER_ALLIANCE_TIER_3, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_LEATHER_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_LEATHER_ALLIANCE_TIER_3, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.80) && sWarEffort->IsBellowPercentGathered(material, team, 1.0f))
                {
                    sWarEffort->RemoveNearbyObject(GO_LEATHER_ALLIANCE_TIER_3, unit);

                    if (!unit->FindNearestGameObject(GO_LEATHER_ALLIANCE_TIER_4, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_LEATHER_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_LEATHER_ALLIANCE_TIER_4, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else
                {
                    sWarEffort->RemoveNearbyObject(GO_LEATHER_ALLIANCE_TIER_4, unit);

                    if (!unit->FindNearestGameObject(GO_LEATHER_ALLIANCE_TIER_5, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_LEATHER_ALLIANCE_TIER_1];
                        unit->GetMap()->SummonGameObject(GO_LEATHER_ALLIANCE_TIER_5, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
            }
            else
            {
                if (sWarEffort->IsBellowPercentGathered(material, team, 0.20f))
                {
                    if (!unit->FindNearestGameObject(GO_LEATHER_HORDE_INITIAL, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_LEATHER_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_LEATHER_HORDE_INITIAL, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }

                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.20f) && sWarEffort->IsBellowPercentGathered(material, team, 0.40f))
                {
                    sWarEffort->RemoveNearbyObject(GO_METAL_HORDE_INITIAL, unit);

                    if (!unit->FindNearestGameObject(GO_LEATHER_HORDE_TIER_1, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_LEATHER_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_LEATHER_HORDE_TIER_1, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.40f) && sWarEffort->IsBellowPercentGathered(material, team, 0.60f))
                {
                    sWarEffort->RemoveNearbyObject(GO_METAL_HORDE_INITIAL, unit);

                    if (!unit->FindNearestGameObject(GO_LEATHER_HORDE_TIER_2, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_LEATHER_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_LEATHER_HORDE_TIER_2, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.60f) && sWarEffort->IsBellowPercentGathered(material, team, 0.80))
                {
                    sWarEffort->RemoveNearbyObject(GO_LEATHER_HORDE_TIER_2, unit);

                    if (!unit->FindNearestGameObject(GO_LEATHER_HORDE_TIER_3, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_LEATHER_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_LEATHER_HORDE_TIER_3, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else if (!sWarEffort->IsBellowPercentGathered(material, team, 0.80f) && sWarEffort->IsBellowPercentGathered(material, team, 1.0f))
                {
                    sWarEffort->RemoveNearbyObject(GO_LEATHER_HORDE_TIER_3, unit);

                    if (!unit->FindNearestGameObject(GO_LEATHER_HORDE_TIER_4, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_LEATHER_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_LEATHER_HORDE_TIER_4, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
                else
                {
                    sWarEffort->RemoveNearbyObject(GO_LEATHER_HORDE_TIER_4, unit);

                    if (!unit->FindNearestGameObject(GO_LEATHER_HORDE_TIER_5, 50.0f))
                    {
                        Position pos = WarEffortGameobjectPositions[GO_LEATHER_HORDE_INITIAL];
                        unit->GetMap()->SummonGameObject(GO_LEATHER_HORDE_TIER_5, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 14 * DAY * MINUTE);
                    }
                }
            }
            break;
        default:
            break;
    }
};

uint32 WarEffort::GetAccumulatedMaterials(uint8 material, uint8 team)
{
    switch (material)
    {
        case MATERIAL_CAT_BANDAGES:
            if (team == TEAM_ALLIANCE)
            {
                return sWarEffort->materialsAlliance[MATERIAL_LINEN] + sWarEffort->materialsAlliance[MATERIAL_SILK] + sWarEffort->materialsAlliance[MATERIAL_RUNECLOTH_A];
            }
            else
            {
                return sWarEffort->materialsHorde[MATERIAL_WOOL] + sWarEffort->materialsHorde[MATERIAL_MAGEWEAVE] + sWarEffort->materialsHorde[MATERIAL_RUNECLOTH_B];
            }
        case MATERIAL_CAT_FOOD:
            if (team == TEAM_ALLIANCE)
            {
                return sWarEffort->materialsAlliance[MATERIAL_ALBACORE] + sWarEffort->materialsAlliance[MATERIAL_RAPTOR] + sWarEffort->materialsAlliance[MATERIAL_YELLOWTAIL_A];
            }
            else
            {
                return sWarEffort->materialsHorde[MATERIAL_WOLF] + sWarEffort->materialsHorde[MATERIAL_SALMON] + sWarEffort->materialsHorde[MATERIAL_YELLOWTAIL_H];
            }
        case MATERIAL_CAT_HERBS:
            if (team == TEAM_ALLIANCE)
            {
                return sWarEffort->materialsAlliance[MATERIAL_STRANGLEKELP] + sWarEffort->materialsAlliance[MATERIAL_ARTHAS_TEARS] + sWarEffort->materialsAlliance[MATERIAL_PURPLE_LOTUS_A];
            }
            else
            {
                return sWarEffort->materialsHorde[MATERIAL_PEACEBLOOM] + sWarEffort->materialsHorde[MATERIAL_FIREBLOOM] + sWarEffort->materialsHorde[MATERIAL_PURPLE_LOTUS_H];
            }
        case MATERIAL_CAT_METAL:
            if (team == TEAM_ALLIANCE)
            {
                return sWarEffort->materialsAlliance[MATERIAL_IRON] + sWarEffort->materialsAlliance[MATERIAL_THORIUM] + sWarEffort->materialsAlliance[MATERIAL_COOPER_A];
            }
            else
            {
                return sWarEffort->materialsHorde[MATERIAL_TIN] + sWarEffort->materialsHorde[MATERIAL_MITHRIL] + sWarEffort->materialsHorde[MATERIAL_COOPER_H];
            }
        case MATERIAL_CAT_LEATHER:
            if (team == TEAM_ALLIANCE)
            {
                return sWarEffort->materialsAlliance[MATERIAL_LIGHT_LEATHER] + sWarEffort->materialsAlliance[MATERIAL_MEDIUM_LEATHER] + sWarEffort->materialsAlliance[MATERIAL_THICK_LEATHER_A];
            }
            else
            {
                return sWarEffort->materialsHorde[MATERIAL_HEAVY_LEATHER] + sWarEffort->materialsHorde[MATERIAL_RUGGER_LEATHER] + sWarEffort->materialsHorde[MATERIAL_THICK_LEATHER_B];
            }
    }

    return 0;
}

std::string WarEffort::PrintOutMaterialCount(uint8 team)
{
    std::string output;

    if (team == TEAM_ALLIANCE)
    {
        for (WarEffortData data : WarEffortMaterialsAlliance)
        {
            if (Quest const* quest = sObjectMgr->GetQuestTemplate(data.QuestId))
            {
                if (ItemTemplate const* item = sObjectMgr->GetItemTemplate(quest->RequiredItemId[0]))
                {
                    output.append(item->Name1 + " (" + Acore::ToString(materialsAlliance[data.Material]) + ")\n");
                }
            }
        }
    }
    else
    {
        for (WarEffortData data : WarEffortMaterialsHorde)
        {
            if (Quest const* quest = sObjectMgr->GetQuestTemplate(data.QuestId))
            {
                if (ItemTemplate const* item = sObjectMgr->GetItemTemplate(quest->RequiredItemId[0]))
                {
                    output.append(item->Name1 + " (" + Acore::ToString(materialsHorde[data.Material]) + ")\n");
                }
            }
        }
    }

    return output;
};

// Add player scripts
class ModAQWarEffortPlayerScript : public PlayerScript
{
public:
    ModAQWarEffortPlayerScript() : PlayerScript("ModAQWarEffortPlayerScript") { }

    void OnPlayerCompleteQuest(Player* player, Quest const* quest)
    {
        if (player->GetTeamId() == TEAM_ALLIANCE)
        {
            for (WarEffortData data : WarEffortMaterialsAlliance)
            {
                if (quest->GetQuestId() == data.QuestId || quest->GetQuestId() == data.QuestId + 1 /* Repeatable ones */)
                {
                    ++sWarEffort->materialsAlliance[data.Material];

                    if (player->IsGameMaster())
                    {
                        ChatHandler(player->GetSession()).SendSysMessage("WarEffort: Quest turned in, updating scores.");
                        ChatHandler(player->GetSession()).SendSysMessage(sWarEffort->PrintOutMaterialCount(player->GetTeamId()));
                    }

                    sWarEffort->SetSaveStatus(true);
                    sWarEffort->CheckGoal(player, data.MaterialCategory, player->GetTeamId());
                }
            }
        }
        else
        {
            for (WarEffortData data : WarEffortMaterialsHorde)
            {
                if (quest->GetQuestId() == data.QuestId || quest->GetQuestId() == data.QuestId + 1 /* Repeatable ones */)
                {
                    ++sWarEffort->materialsHorde[data.Material];

                    if (player->IsGameMaster())
                    {
                        ChatHandler(player->GetSession()).SendSysMessage("WarEffort: Quest turned in, updating scores.");
                        ChatHandler(player->GetSession()).SendSysMessage(sWarEffort->PrintOutMaterialCount(player->GetTeamId()));
                    }

                    sWarEffort->SetSaveStatus(true);
                    sWarEffort->CheckGoal(player, data.MaterialCategory, player->GetTeamId());
                }
            }
        }
    }
};

class ModWarEffortWorldScript : public WorldScript
{
public:
    ModWarEffortWorldScript() : WorldScript("ModWarEffortWorldScript") { }

    void OnAfterConfigLoad(bool reload) override
    {
        ScheduleTasks();
    }

    void OnStartup() override
    {
        ScheduleTasks();
        sWarEffort->LoadData();
    }

    void OnUpdate(uint32 diff) override
    {
        if (sWarEffort->IsEnabled())
        {
            _scheduler.Update(diff);
        }
    }

    void ScheduleTasks()
    {
        if (sWarEffort->IsEnabled())
        {
            _scheduler.CancelAll();

            _scheduler.Schedule(1min, [this](TaskContext context)
            {
                if (sWarEffort->IsSaveNeeded())
                {
                    sWarEffort->SaveData();
                    sWarEffort->SetSaveStatus(false);
                }

                if (sWarEffort->IsEnabled())
                {
                    context.Repeat();
                }
            });
        }
    }

    void OnShutdownInitiate(ShutdownExitCode /*code*/, ShutdownMask /*mask*/) override
    {
        if (sWarEffort->IsEnabled())
        {
            _scheduler.CancelAll();

            if (sWarEffort->IsSaveNeeded())
            {
                sWarEffort->SaveData();
                sWarEffort->SetSaveStatus(false);
            }
        }
    }

private:
    TaskScheduler _scheduler;
};

// Add all scripts in one
void ModAQWarEffortPlayerScripts()
{
    new ModAQWarEffortPlayerScript();
    new ModWarEffortWorldScript();
}
