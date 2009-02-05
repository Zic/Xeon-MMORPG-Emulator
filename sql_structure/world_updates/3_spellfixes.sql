ALTER TABLE spellfixes DROP SpellGroupType;
ALTER TABLE spellfixes DROP groupRelation0;
ALTER TABLE spellfixes DROP groupRelation1;
ALTER TABLE spellfixes DROP groupRelation2;

ALTER TABLE spellfixes ADD effect0ClassMask0 int4 UNSIGNED NOT NULL DEFAULT 0;
ALTER TABLE spellfixes ADD effect0ClassMask1 int4 UNSIGNED NOT NULL DEFAULT 0;
ALTER TABLE spellfixes ADD effect0ClassMask2 int4 UNSIGNED NOT NULL DEFAULT 0;
ALTER TABLE spellfixes ADD effect1ClassMask0 int4 UNSIGNED NOT NULL DEFAULT 0;
ALTER TABLE spellfixes ADD effect1ClassMask1 int4 UNSIGNED NOT NULL DEFAULT 0;
ALTER TABLE spellfixes ADD effect1ClassMask2 int4 UNSIGNED NOT NULL DEFAULT 0;
ALTER TABLE spellfixes ADD effect2ClassMask0 int4 UNSIGNED NOT NULL DEFAULT 0;
ALTER TABLE spellfixes ADD effect2ClassMask1 int4 UNSIGNED NOT NULL DEFAULT 0;
ALTER TABLE spellfixes ADD effect2ClassMask2 int4 UNSIGNED NOT NULL DEFAULT 0;

TRUNCATE TABLE spellfixes;

--
-- Mage - Frost Tree
--

-- [Mage] Fingers of Frost
INSERT INTO spellfixes(spellId, procChance, effect0ClassMask0) VALUES(44543, 7, 0x100020);
INSERT INTO spellfixes(spellId, procChance, effect0ClassMask0) VALUES(44545, 14, 0x100020);

-- [Mage] Improved Counterspell
INSERT INTO spellfixes(spellId, effect0ClassMask0) VALUES(11255, 0x4000);
INSERT INTO spellfixes(spellId, effect0ClassMask0) VALUES(12598, 0x4000);

-- [Mage] Brain Freeze
INSERT INTO spellfixes(spellId, effect0ClassMask0) VALUES(44546, 0x100020);
INSERT INTO spellfixes(spellId, effect0ClassMask0) VALUES(44548, 0x100020);
INSERT INTO spellfixes(spellId, effect0ClassMask0) VALUES(44549, 0x100020);


--
-- Mage - Fire Tree
--

-- [Mage] Impact
INSERT INTO spellfixes(spellId, effect0ClassMask0) VALUES(11103, 0xD0C020DA1AF7);
INSERT INTO spellfixes(spellId, effect0ClassMask0) VALUES(12357, 0xD0C020DA1AF7);
INSERT INTO spellfixes(spellId, effect0ClassMask0) VALUES(12358, 0xD0C020DA1AF7);


--
-- Mage - Arcane Tree
--

-- [Mage] Improved Blink
INSERT INTO spellfixes(spellId, procFlags, effect1ClassMask0) VALUES(31569, 0x10, 0x10000);
INSERT INTO spellfixes(spellId, procFlags, effect1ClassMask0) VALUES(31570, 0x10, 0x10000);

-- [Mage] Missile Barrage
INSERT INTO spellfixes(spellId, effect0ClassMask0, effect0ClassMask1) VALUES(44404, 0x20100021, 0x8000);
INSERT INTO spellfixes(spellId, effect0ClassMask0, effect0ClassMask1) VALUES(54486, 0x20100021, 0x8000);
INSERT INTO spellfixes(spellId, effect0ClassMask0, effect0ClassMask1) VALUES(54488, 0x20100021, 0x8000);
INSERT INTO spellfixes(spellId, effect0ClassMask0, effect0ClassMask1) VALUES(54489, 0x20100021, 0x8000);
INSERT INTO spellfixes(spellId, effect0ClassMask0, effect0ClassMask1) VALUES(54490, 0x20100021, 0x8000);

--
-- Priest - Discipline
--

-- [Priest] Grace
INSERT INTO spellfixes(spellId, procFlags, effect0ClassMask0, effect0ClassMask1) VALUES(47516, 0x10, 0x1800, 0x800000);
INSERT INTO spellfixes(spellId, procFlags, effect0ClassMask0, effect0ClassMask1) VALUES(47517, 0x10, 0x1800, 0x800000);

--
-- Priest - Holy
--

--
-- Priest - Shadow
--

-- [Priest] Misery
INSERT INTO spellfixes(spellId, procFlags, effect0ClassMask0, effect0ClassMask1, effect0ClassMask2) VALUES(33191, 0x10, 0x8000, 0x400, 0x40);
INSERT INTO spellfixes(spellId, procFlags, effect0ClassMask0, effect0ClassMask1, effect0ClassMask2) VALUES(33192, 0x10, 0x8000, 0x400, 0x40);
INSERT INTO spellfixes(spellId, procFlags, effect0ClassMask0, effect0ClassMask1, effect0ClassMask2) VALUES(33193, 0x10, 0x8000, 0x400, 0x40);

--
-- Paladin - Holy
--

-- [Mage] Illumination
INSERT INTO spellfixes(spellId, procFlags, effect0ClassMask0) VALUES(20210, 0x40000000, 0xC0200000);
INSERT INTO spellfixes(spellId, procFlags, effect0ClassMask0) VALUES(20212, 0x40000000, 0xC0200000);
INSERT INTO spellfixes(spellId, procFlags, effect0ClassMask0) VALUES(20213, 0x40000000, 0xC0200000);
INSERT INTO spellfixes(spellId, procFlags, effect0ClassMask0) VALUES(20214, 0x40000000, 0xC0200000);
INSERT INTO spellfixes(spellId, procFlags, effect0ClassMask0) VALUES(20215, 0x40000000, 0xC0200000);
