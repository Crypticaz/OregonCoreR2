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
 * Scripts for spells with SPELLFAMILY_HUNTER, SPELLFAMILY_PET and SPELLFAMILY_GENERIC spells used by hunter players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_hun_".
 */

#include "ScriptPCH.h"

enum HunterSpells
{
    HUNTER_SPELL_READINESS                       = 23989,
    HUNTER_SPELL_BESTIAL_WRATH                   = 19574
};

class spell_hun_readiness_SpellScript : public SpellScript
{
    void HandleDummy(SpellEffIndex effIndex)
    {
        Unit* caster = GetCaster();
        if (caster->GetTypeId() != TYPEID_PLAYER)
            return;

        // immediately finishes the cooldown on your other Hunter abilities except Bestial Wrath
        const PlayerSpellMap& cm = caster->ToPlayer()->GetSpellMap();
        for (PlayerSpellMap::const_iterator itr = cm.begin(); itr != cm.end();)
        {
            SpellEntry const *spellInfo = sSpellStore.LookupEntry(itr->first);

            if (spellInfo->SpellFamilyName == SPELLFAMILY_HUNTER &&
                spellInfo->Id != HUNTER_SPELL_READINESS &&
                spellInfo->Id != HUNTER_SPELL_BESTIAL_WRATH &&
                GetSpellRecoveryTime(spellInfo) > 0)
                caster->ToPlayer()->RemoveSpellCooldown((itr++)->first,true);
            else
                ++itr;
        }
    }

    void Register()
    {
        // add dummy effect spell handler to Readiness
        EffectHandlers += EffectHandlerFn(spell_hun_readiness_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

SpellScript * GetSpellScript_spell_hun_readiness()
{
    return new spell_hun_readiness_SpellScript();
}

void AddSC_hunter_spell_scripts()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "spell_hun_readiness";
    newscript->GetSpellScript = &GetSpellScript_spell_hun_readiness;
    newscript->RegisterSelf();
}
