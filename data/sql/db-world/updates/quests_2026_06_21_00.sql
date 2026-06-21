-- Fix worldserver errors that occur due to these entries being deleted from creature table in the quests.sql queries but not from game_event_creature
DELETE FROM `game_event_creature` WHERE `guid` IN (
    83113, 83114, 83115, 83116, 83120, 83121, 83122, 83123, 83124, 83125,
    83126, 83127, 83128, 83129, 83130, 83131, 83132, 83133, 83134, 83140,
    83141, 83142, 83143, 83144, 83148, 83149, 83150, 83151, 83152, 83153,
    83154, 83155, 83156, 83157, 83158, 83159, 83160, 83161, 83162, 83168
);

