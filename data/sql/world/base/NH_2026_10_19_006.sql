-- Backup original values
CREATE TABLE IF NOT EXISTS gameobject_loot_template_backup_gathering AS
SELECT Entry, Item, MinCount, MaxCount
FROM gameobject_loot_template
WHERE Comment LIKE '%Vein%Ore';

INSERT IGNORE INTO gameobject_loot_template_backup_gathering
SELECT Entry, Item, MinCount, MaxCount
FROM gameobject_loot_template
WHERE Comment LIKE '%Deposit%Ore';

INSERT IGNORE INTO gameobject_loot_template_backup_gathering
SELECT Entry, Item, MinCount, MaxCount
FROM gameobject_loot_template
WHERE Comment REGEXP '^(.+) - \\1$';

-- Double Veins and Deposits drop
UPDATE gameobject_loot_template i
JOIN gameobject_loot_template_backup_gathering b on i.Entry = b.Entry AND i.Item = b.Item 
SET i.MinCount = b.MinCount * 2, i.MaxCount = b.MaxCount * 2
WHERE i.Entry = b.Entry AND i.Item = b.Item;