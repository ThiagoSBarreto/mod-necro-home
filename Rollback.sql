START TRANSACTION;

UPDATE item_template i
JOIN item_template_stack_backup b ON i.entry = b.entry
SET i.stackable = b.stackable;

UPDATE creature_loot_template i
JOIN creature_loot_template_backup b on i.Entry = b.Entry
SET i.Chance = b.Chance
WHERE i.QuestRequired = 1;

UPDATE creature_loot_template i
JOIN creature_loot_template_backup_cloth b on i.Entry = b.Entry AND i.Item = b.Item
SET i.MinCount = b.MinCount, i.MaxCount = b.MaxCount
WHERE i.Entry = b.Entry AND i.Item = b.Item;

UPDATE gameobject_loot_template i
JOIN gameobject_loot_template_backup_gathering b on i.Entry = b.Entry AND i.Item = b.Item 
SET i.MinCount = b.MinCount, i.MaxCount = b.MaxCount
WHERE i.ENtry = b.Entry AND i.Item = b.Item;

UPDATE skinning_loot_template i
JOIN skinning_loot_template_backup b on i.Entry = b.Entry AND i.Item = b.Item
SET i.MinCount = b.MinCount, i.MaxCount = b.MaxCount
WHERE i.Entry = b.Entry AND i.Item = b.Item;

DELETE FROM playercreateinfo_item WHERE itemid = 2901;
DELETE FROM playercreateinfo_item WHERE itemid = 4470;
DELETE FROM playercreateinfo_item WHERE itemid = 4471;
DELETE FROM playercreateinfo_item WHERE itemid = 5956;
DELETE FROM playercreateinfo_item WHERE itemid = 6256;
DELETE FROM playercreateinfo_item WHERE itemid = 23162;
DELETE FROM playercreateinfo_item WHERE itemid = 7005;

COMMIT;