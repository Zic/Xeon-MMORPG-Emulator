/* Temp fix for potions. Lets them have cooldown not affected by combat like in pre 3.0 */
UPDATE items SET spellcategory_1 = 2000 where spellcategory_1 = 4;