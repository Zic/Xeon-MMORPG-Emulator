/* 
auraimmune_flag
This mask can make Npc immune for one (or more!) effects.
Aura          Flag
NONE             0
CONFUSE          1
CHARM            2
FEAR             4
STUN             8
PACIFY          16
ROOT            32
SILENCE         64
INCSPEED       128
DECSPEED       256
TRANSFORM      512
TAUNT         1024
BLEED         2048
POISON        4096
MANALEECH     8192
LEECH        16384 
/*

ALTER TABLE creature_proto ADD COLUMN auraimmune_flag int(11)  DEFAULT 0 NOT NULL  AFTER extra_a9_flags;