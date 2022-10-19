DELETE FROM `creature_text` WHERE `CreatureID`=15693;
INSERT INTO `creature_text` (`CreatureID`,`GroupID`,`ID`,`Text`,`Type`,`Language`,`Probability`,`Emote`,`Duration`,`Sound`,`BroadcastTextId`, `TextRange`, `comment`) VALUES
(15693, 0, 0, '$n, Champion of the Bronze Dragonflight, has rung the Scarab Gong. The ancient gates of Ahn\'Qiraj open, revealing the horrors of a forgotten war...', 16, 0, 100, 1, 0, 0, 11427, 4, 'EMOTE_AQ_GONG_1'),
(15693, 1, 0, 'Massive Qiraji resonating crystals break through the earthen crust of Kalimdor. Colossal creatures made of obsidian stone breach the freshly broken land...', 16, 0, 100, 1, 0, 0, 11432, 4, 'EMOTE_AQ_GONG_2'),
(15693, 2, 0, 'Colossus of Zora casts its massive shadow upon the whole of Silithus.', 16, 0, 100, 1, 0, 0, 0, 4, 'EMOTE_AQ_GONG_3'),
(15693, 3, 0, 'Colossus of Ashi breaks free of its cocoon beneath Hive\'Ashi.', 16, 0, 100, 1, 0, 0, 0, 4, 'EMOTE_AQ_GONG_4'),
(15693, 4, 0, 'Colossus of Regal hears the call to battle and rises to serve its master.', 16, 0, 100, 1, 0, 0, 0, 4, 'EMOTE_AQ_GONG_5');

DELETE FROM `gameobject_queststarter` WHERE `id` = 180718;
INSERT INTO `gameobject_queststarter` (`id`, `quest`) VALUES
(180718, 8743);

DELETE FROM `gameobject_questender` WHERE `id` = 180718;
INSERT INTO `gameobject_questender` (`id`, `quest`) VALUES
(180718, 8743);

UPDATE `gameobject_template` SET `type` = 2 WHERE `entry` = 180718;
