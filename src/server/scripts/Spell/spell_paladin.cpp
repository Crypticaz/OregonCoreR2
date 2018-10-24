/*
 * Copyright (C) 2008-2018 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Scripts for spells with SPELLFAMILY_SHAMAN and SPELLFAMILY_GENERIC spells used by paladin players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_pal_".
 */

#include "ScriptPCH.h"

enum PaladinSpells
{
    PALADIN_SPELL_HOLY_SHOCK_R1                  = 20473,
    PALADIN_SPELL_HOLY_SHOCK_R1_DAMAGE           = 25912,
    PALADIN_SPELL_HOLY_SHOCK_R1_HEALING          = 25914,
    PALADIN_SPELL_HOLY_SHOCK_R2                  = 20929,
    PALADIN_SPELL_HOLY_SHOCK_R2_DAMAGE           = 25911,
    PALADIN_SPELL_HOLY_SHOCK_R2_HEALING          = 25913,
    PALADIN_SPELL_HOLY_SHOCK_R3                  = 20930,
    PALADIN_SPELL_HOLY_SHOCK_R3_DAMAGE           = 25902,
    PALADIN_SPELL_HOLY_SHOCK_R3_HEALING          = 25903,
    PALADIN_SPELL_HOLY_SHOCK_R4                  = 27174,
    PALADIN_SPELL_HOLY_SHOCK_R4_DAMAGE           = 27176,
    PALADIN_SPELL_HOLY_SHOCK_R4_HEALING          = 27175,
    PALADIN_SPELL_HOLY_SHOCK_R5                  = 33072,
    PALADIN_SPELL_HOLY_SHOCK_R5_DAMAGE           = 33073,
    PALADIN_SPELL_HOLY_SHOCK_R5_HEALING          = 33074
};

class spell_pal_holy_shock_SpellScript : public SpellScript
{
    bool Validate(SpellEntry const * spellEntry)
    {
        if (!sSpellStore.LookupEntry(PALADIN_SPELL_HOLY_SHOCK_R1))
            return false;
        if (!sSpellStore.LookupEntry(PALADIN_SPELL_HOLY_SHOCK_R1_DAMAGE))
            return false;
        if (!sSpellStore.LookupEntry(PALADIN_SPELL_HOLY_SHOCK_R1_HEALING))
            return false;

        if (!sSpellStore.LookupEntry(PALADIN_SPELL_HOLY_SHOCK_R2))
            return false;
        if (!sSpellStore.LookupEntry(PALADIN_SPELL_HOLY_SHOCK_R2_DAMAGE))
            return false;
        if (!sSpellStore.LookupEntry(PALADIN_SPELL_HOLY_SHOCK_R2_HEALING))
            return false;

        if (!sSpellStore.LookupEntry(PALADIN_SPELL_HOLY_SHOCK_R3))
            return false;
        if (!sSpellStore.LookupEntry(PALADIN_SPELL_HOLY_SHOCK_R3_DAMAGE))
            return false;
        if (!sSpellStore.LookupEntry(PALADIN_SPELL_HOLY_SHOCK_R3_HEALING))
            return false;

        if (!sSpellStore.LookupEntry(PALADIN_SPELL_HOLY_SHOCK_R4))
            return false;
        if (!sSpellStore.LookupEntry(PALADIN_SPELL_HOLY_SHOCK_R4_DAMAGE))
            return false;
        if (!sSpellStore.LookupEntry(PALADIN_SPELL_HOLY_SHOCK_R4_HEALING))
            return false;

        if (!sSpellStore.LookupEntry(PALADIN_SPELL_HOLY_SHOCK_R5))
            return false;
        if (!sSpellStore.LookupEntry(PALADIN_SPELL_HOLY_SHOCK_R5_DAMAGE))
            return false;
        if (!sSpellStore.LookupEntry(PALADIN_SPELL_HOLY_SHOCK_R5_HEALING))
            return false;

        return true;
    }

    void HandleDummy(SpellEffIndex effIndex)
    {
        if (Unit *unitTarget = GetHitUnit())
        {
            Unit *caster = GetCaster();

            int hurt = 0;
            int heal = 0;

            switch(GetSpellInfo()->Id)
            {
                case PALADIN_SPELL_HOLY_SHOCK_R1:
                    hurt = PALADIN_SPELL_HOLY_SHOCK_R1_DAMAGE;
                    heal = PALADIN_SPELL_HOLY_SHOCK_R1_HEALING;
                    break;
                case PALADIN_SPELL_HOLY_SHOCK_R2:
                    hurt = PALADIN_SPELL_HOLY_SHOCK_R2_DAMAGE;
                    heal = PALADIN_SPELL_HOLY_SHOCK_R2_HEALING;
                    break;
                case PALADIN_SPELL_HOLY_SHOCK_R3:
                    hurt = PALADIN_SPELL_HOLY_SHOCK_R3_DAMAGE;
                    heal = PALADIN_SPELL_HOLY_SHOCK_R3_HEALING;
                    break;
                case PALADIN_SPELL_HOLY_SHOCK_R4:
                    hurt = PALADIN_SPELL_HOLY_SHOCK_R4_DAMAGE;
                    heal = PALADIN_SPELL_HOLY_SHOCK_R4_HEALING;
                    break;
                case PALADIN_SPELL_HOLY_SHOCK_R5:
                    hurt = PALADIN_SPELL_HOLY_SHOCK_R5_DAMAGE;
                    heal = PALADIN_SPELL_HOLY_SHOCK_R5_HEALING;
                    break;
                default:
                    sLog.outError("spell_pal_holy_shock_SpellScript::HandleDummy: Spell %u not handled in HS",GetSpellInfo()->Id);
                    return;
            }

            if (caster->IsFriendlyTo(unitTarget))
                caster->CastSpell(unitTarget, heal, true, 0);
            else
                caster->CastSpell(unitTarget, hurt, true, 0);
        }
    }

    void Register()
    {
        // add dummy effect spell handler to Holy Shock
        EffectHandlers += EffectHandlerFn(spell_pal_holy_shock_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

SpellScript * GetSpellScript_spell_pal_holy_shock()
{
    return new spell_pal_holy_shock_SpellScript();
}

void AddSC_paladin_spell_scripts()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "spell_pal_holy_shock";
    newscript->GetSpellScript = &GetSpellScript_spell_pal_holy_shock;
    newscript->RegisterSelf();
}

