-- Backup original values
CREATE TABLE IF NOT EXISTS creature_loot_template_backup AS
SELECT Entry, Chance, QuestRequired
FROM creature_loot_template
WHERE QuestRequired = 1;

-- 100% drop chance for quest items
UPDATE creature_loot_template
SET Chance = 100
WHERE QuestRequired = 1;