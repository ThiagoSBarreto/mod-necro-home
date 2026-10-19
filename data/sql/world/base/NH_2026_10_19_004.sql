-- Backup original values
CREATE TABLE IF NOT EXISTS creature_loot_template_backup
LIKE creature_loot_template;

INSERT IGNORE INTO creature_loot_template_backup
SELECT *
FROM creature_loot_template
WHERE QuestRequired = 1;

-- 100% drop chance for quest items
UPDATE creature_loot_template
SET Chance = 100
WHERE QuestRequired = 1;