/**
 *	базовая база
 * set_weather(fog_density[], fog_color[], sky_name[], light_lvl[]) - устанавливает погоду на серваке спользовать в plugin_init | "0.0003", "202 35 252", "sky161", "h"
 *
 *	параметры игрока
 * set_hp(id, Float:value)  - устанавливает хп | id, 5.0
 * add_hp(id, Float:value) - добавляет хп | id, 5.0
 * set_arm(id, Float:value) - устанавливает броню | id, 5.0
 * add_arm(id, Float:value) - добавляет броню | id, 5.0
 * set_speed(id, Float:value) - устанавливает макс скорость | id, 5.0
 * set_grav(id, Float:value) - устанавливает грав. (0.0 - 1.0) | id, 0.3
 * 
 *	внешность игрока/рук и тд
 * choose_skin(id, skinName[]) - меняет скин по названию скина | id, "models/player/m_z_Invisible/m_z_Invisible.mdl"
 * give_aura_eff(id, r, g, b, power) - разные эффекты ентити (например свечение) подробнее в инете | id, kRenderFxGlowShell, 0, 0, 0, kRenderNormal, 0
 * tike_aura_eff(id) - убирает ауру вокруг игрока | id
 * change_knife_to_zombie(id, v_knife[], zm_id) - анимка заражения + смена рук на зомби | id, "model", zm_id
 *
 *	инфа для игроков
 * print(id, input[], any:...) - пишет в чат | id, "num %d", d
 * print_mess(id, codeMes)  - пишет сообщение по его коду | id, 0
 *
 *	эффекты
 * screen_shine(id, r, g, b, power, randow_color) - свечение экрана | id, 100, 100, 100, 16, 0
 * create_spr_in_player(id, spr, size) - создает спрайт в объекте | id "spr", 16
 * create_spr_point_point(id, g_trailSpr, timeLife, width, amplitude, r, g, b) - спарайт между 2-я точками игрок + куда смотрит | id, g_trailSpr, 30, 10, 5, 0, 0, 255
 * create_spr_player_point(id, g_trailSpr, width) - спрайт между точкой куда смотрит и игроком | id, g_trailSpr, 10
 * create_cycle_spr_in_player(id, timeLife, width, r, g, b, g_trailSpr) - создает круговой спрайт в объекте | id, 1.0, 100, 255, 255, 255, g_trailSpr
 * create_trail_spr_after_obj(id, life, width, r, g, b, g_trailSpr) - создает спрайт-хвост за объектом | id, 1.0, 100, 255, 255, 255, g_trailSpr
 * create_splash_spr_obj(id, spr, count, life, scale, noise, speed) - создает много спрайтов в объекте | id, "spr", 10, 3.0, 16, 20, 10
 * create_light_spr_obj(id, radius, r, g, b, life, speed) - создает световой спрайт в объекте | id, 100, 255, 255, 255, 3.0, 100
 *
 *	для разработки
 * get_number_players_in_server() - возвращает кол-во игроков на сервере | 
 * combStr(shablon[], str[]) - добавляет %s по шаблону | "new str = %s", "str!!!"
 *	разное
 * update_frags(attacker, victim, frags, deaths, scoreboard) - иметирует убийство например если умирает от энтити | id, id, 1, 1, 1
 *
 *	ентити
 * new_entity(typeSpawn, id, modelName[], classmane[], Float:timeLife, animId, animSpeed, thinkTime, solidType, moveType) - создает и return entity | 0, id, "model", "classname", 1.0, 0, 0, 0.0, 0, 0
 * damage_in_radius(attacker, iEntity, distance, damage) - ентити наносит урон в радиусе | id, entity, 150, 1
 * kill_by_entity(victim, attacker, weaponId) - ентити убивает игрока + киллбар | id, id, 3
 * set_entity_vector_speed(typemove, speed, id, iEntity) - меняет направление и скорость ентити | 0-по взгляну 1-хз, 330, id, entity
 * draw_into_oneself(attacker ,iEntity, distance, Float:speed, isDamage, damage) - затягивает игроков в ентити | id, entity, 300, 300.0, 0or1, 4
 *
 * 	оружие
 * drop_weapons(id, dropwhat) - дропает оружие | id, 1or2
 * set_gun_model(id, V_Models[], P_Models[]) - меняет модель оружия | id, "V_Models", "P_Models"
 * UTIL_PlayWeaponAnimation(Player, Sequence) - запускает анимку оружия | id, 2
 * give_gun(id, weapon_type) - дает оружие - id, (10, 11, 12, 13, 20)
 */
 
#include <Krol_conts>
#include <reapi>
#include <reapi_engine>
 
public set_hp(id, Float:value){set_pev(id, pev_health, value);}
public add_hp(id, Float:value){ set_pev(id, pev_health, pev(id, pev_health) + value); }
public set_arm(id, Float:value){set_pev(id, pev_armorvalue, value);}
public add_arm(id, Float:value){set_pev(id, pev_armorvalue, pev(id, pev_armorvalue) + value);}
public set_speed(id, Float:value){set_user_maxspeed(id, value);}
public set_grav(id, Float:value){set_user_gravity(id, value);}

public print(id, input[], any:...){
	new count = 1, players[32]
	static msg[191]
	vformat(msg, 190, input, 3)

	replace_all(msg, 190, "!g", "^4")
	replace_all(msg, 190, "!y", "^1")
	replace_all(msg, 190, "!t", "^3")

	if (id) players[0] = id; else get_players(players, count, "ch")
	{
		for (new i = 0; i < count; i++)
		{
			if (is_user_connected(players[i]))
			{
				message_begin(MSG_ONE_UNRELIABLE, get_user_msgid("SayText"), _, players[i]);
				write_byte(players[i]);
				write_string(msg);
				message_end();
			}
		}
	}
}

public choose_skin(id, skinName[]){
	if( !is_user_connected(id) ) return PLUGIN_HANDLED

	cs_set_user_model(id, skinName)
	return PLUGIN_HANDLED
}

public give_aura_eff(id, r, g, b, power){my_fm_set_rendering(id, kRenderFxGlowShell, r, g, b, kRenderNormal, power); }
public tike_aura_eff(id){my_fm_set_rendering(id, kRenderFxGlowShell, 0, 0, 0, kRenderNormal, 0); }

public set_weather(fog_density[], fog_color[], sky_name[], light_lvl[]){
	new pEnt = engfunc(EngFunc_CreateNamedEntity, engfunc(EngFunc_AllocString, "env_fog"))
	if (pEnt){
		set_kvd(0, KV_ClassName, "env_fog");
		set_kvd(0, KV_KeyName, "density");
		set_kvd(0, KV_Value, fog_density );
		set_kvd(0, KV_fHandled, 0);

		dllfunc(DLLFunc_KeyValue, pEnt, 0);

		set_kvd(0, KV_KeyName, "rendercolor");
		set_kvd(0, KV_Value, fog_color);

		dllfunc(DLLFunc_KeyValue, pEnt, 0);
	}
	server_cmd("sv_skyname %s", sky_name)
	set_lights(light_lvl)
}

public update_frags(attacker, victim, frags, deaths, scoreboard){
	new g_msgScoreInfo = get_user_msgid("ScoreInfo")
	
	set_pev(attacker, pev_frags, float(pev(attacker, pev_frags) + frags))
	set_pdata_int(victim, OFFSET_CSDEATHS, cs_get_user_deaths(victim) + deaths, OFFSET_LINUX)

	if (scoreboard){
		message_begin(MSG_BROADCAST, g_msgScoreInfo)
		write_byte(attacker) // id
		write_short(pev(attacker, pev_frags)) // frags
		write_short(cs_get_user_deaths(attacker)) // deaths
		write_short(0) // class?
		write_short(1) // team | cs_get_user_team(attacker)
		message_end()

		message_begin(MSG_BROADCAST, g_msgScoreInfo)
		write_byte(victim)
		write_short(pev(victim, pev_frags)) // frags
		write_short(cs_get_user_deaths(victim)) // deaths
		write_short(0) // class?
		write_short(2) // team | cs_get_user_team(victim)
		message_end()
	}
}

public screen_shine(id, r, g, b, power, randow_color){
	message_begin(MSG_ONE, get_user_msgid("ScreenFade"), {0, 0, 0}, id)
	write_short(1<<11)
	write_short(1<<11)
	write_short(0x0001)
	if ( randow_color ){
		write_byte( random_num ( 0,255 ) )
		write_byte( random_num ( 0,255 ) )
		write_byte( random_num ( 0,255 ) )
	}else{
		write_byte(r)
		write_byte(g)
		write_byte(b)
	}
	write_byte(power) // alpha
	message_end()
}

public get_number_players_in_server(){
	new score_players

	for(new iPlayer; iPlayer < 33; iPlayer++){
		if(is_user_connected(iPlayer)){
			score_players++
		}
	}

	return score_players
}

public print_mess(id, codeMes){
	switch(codeMes){
        case 0:{ print(id, "!g[ZP] !yВы !tзомби!");}
		case 1:{ print(id, "!g[ZP] !yУ вас недостаточно !gправ!");}
        case 2:{ print(id, "!g[ZP]!y У вас маленький LVL.");}


		case 10:{ print(id, "!g[SHOP] !yУ вас недостаточно !gаммо!");}
		case 11:{ print(id, "!g[SHOP] !yПодождите, вы !gнедавно !yпокупали это!");}
		case 12:{ print(id, "!g[SHOP] !yВирус слишком сильный! !gАнтидот !yуже !gне поможет!");}

    }
}


public change_knife_to_zombie(id, v_knife[], zm_id){
    set_pev(id, pev_viewmodel, engfunc(EngFunc_AllocString, "models/v_infection.mdl" ));
    set_pev(id, pev_weaponmodel, engfunc(EngFunc_AllocString, "" ))
    screen_shine(id, 255, 255, 0, 40, 0)

    new data[2]
    data[0] = id
    data[1] = zm_id
    set_task(1.0, "task_change_infEff_to_knife", 12345, data, 2)

    return PLUGIN_HANDLED
}

public new_entity(typeSpawn, id, modelName[], className[], Float:timeLife, animId, animSpeed, thinkTime, solidType, moveType, PozZ){
	new iOrigin[3] //Создаем массив для хранение координат
	new Float:fOrigin[3] //Создаем массив для float коодинат

	if (typeSpawn == 0){
		get_user_origin(id, iOrigin, 3) //Получаем координаты куда смотрит игрок
		IVecFVec(iOrigin, fOrigin) //Конвертируем координаты в дробные
		fOrigin[2] = fOrigin[2] + PozZ
	}else if(typeSpawn == 1){
		pev(id, pev_origin, fOrigin) //Получаем координаты игрока
	}

	new iEntity = create_entity("info_target") //Создаем объект info_target

	if(!pev_valid(iEntity)) //Проверяем сущетсвует ли, если нет
		return PLUGIN_HANDLED //Заканчиваем. Дальше нам делать нечего

	set_pev(iEntity, pev_origin, fOrigin) //Присваиваем координаты
	set_pev(iEntity, pev_classname, className) //Присваиваем Classname
	set_pev(iEntity, pev_solid, solidType) //Делаем его непроходимым
	set_pev(iEntity, pev_movetype, moveType) //Не задаем тип движения, во всяком случаи пока
	set_pev(iEntity, pev_sequence, animId) //Выставляем № анимации при создании
	set_pev(iEntity, pev_framerate, animSpeed) //Выставляем скорость анимации
	set_pev(iEntity, pev_nextthink, get_gametime() + thinkTime) //Создаем запуск think

	engfunc(EngFunc_SetModel, iEntity, modelName) //Присваиваем модель
	engfunc(EngFunc_SetSize, iEntity, Float:{-16.0, -16.0, -16.0}, Float:{16.0, 16.0, 16.0}) //Создаем бокс вокруг entity( для прикосновения и не только )
	
	set_task(timeLife, "task_delite_entity", iEntity, _, _, "a", 1)	//запускает режим игры

	return iEntity
}
public damage_in_radius(attacker, iEntity, distance, damage){
	if(!pev_valid(iEntity)) //Проверяем сущетсвует ли, если нет
		return PLUGIN_HANDLED //Заканчиваем. Дальше нам делать нечего

	for(new id = 1; id <= 32; id++){
		if ( !is_user_connected(id) ) continue
		if ( entity_range(id, iEntity) > distance ) continue
		if (id == attacker) continue

		if (pev(id, pev_health) <= 1.0 * damage){
			if(is_user_alive(id)){
				kill_by_entity(id, attacker, 29)
			}
		}else{
			set_pev(id, pev_health, (pev(id, pev_health) - ( 1.0 * damage) ) );
		}
	}
	return PLUGIN_HANDLED
}

public kill_by_entity(victim, attacker, weaponId){
	new g_weapon_names[][] ={
		"", // NULL
		"p228", "shield","scout","grenade","xm1014",
		"c4","mac10","aug","smokegrenade","elite",
		"fiveseven","ump45","sg550","galil","famas",
		"usp","glock18","awp","mp5navy","m249",
		"m3","m4a1","tmp","g3sg1","flashbang",
		"deagle","sg552","ak47","knife","p90"
	}

	user_silentkill(victim)
	make_deathmsg ( attacker, victim, 0, g_weapon_names[29] )
	update_frags(attacker, victim, 1, 0, 1)
}

public set_entity_vector_speed(typemove, speed, id, iEntity){
	new Float:velocity[3]

	if(typemove == 0){ // движение по направлению камеры
		pev(id, pev_v_angle, velocity);
		velocity_by_aim(id, speed, velocity)
		set_pev(iEntity, pev_velocity, velocity);
	}else if(typemove == 1){

	}
}

public draw_into_oneself(attacker ,iEntity, distance, Float:speed, isDamage, damage){
	if(!pev_valid(iEntity)) //Проверяем сущетсвует ли, если нет
		return PLUGIN_HANDLED //Заканчиваем. Дальше нам делать нечего

	for(new id = 1; id <= 32; id++){
		if ( !is_user_connected(id) ) continue
		if ( entity_range(id, iEntity) > distance ) continue
		if (id == attacker) continue

		if(isDamage){
			if (pev(id, pev_health) <= 1.0 * damage){
				if(is_user_alive(id)){
					kill_by_entity(id, attacker, 29)
				}
			}else{
				set_pev(id, pev_health, (pev(id, pev_health) - ( 1.0 * damage) ) );
			}
		}

		static Float: origp[3],Float:origview[3],Float:iVelocity[3];
		pev(id,pev_origin,origp)
		pev(iEntity, pev_origin, origview);
		pev(id,pev_velocity,iVelocity)
		if(Wall1(origview, origp, iEntity))continue;
		get_speed_vector(origp,origview,speed,iVelocity)
		iVelocity[2]=iVelocity[2]+50.0
		set_pev(id,pev_velocity,iVelocity)

	}
	return PLUGIN_HANDLED
}


public create_spr_point_point(id, g_trailSpr, timeLife, width, amplitude, r, g, b){
    new Float:iOrigin[3] //Создаем массив для хранение координат
	new Float:origin[3];
    get_user_origin(id, iOrigin, 3) //Получаем координаты куда смотрит игрок
    get_user_origin(id, origin); // Получаем координаты игрока

	message_begin(MSG_BROADCAST, SVC_TEMPENTITY)
	write_byte(TE_BEAMPOINTS)
	write_coord(origin[0])
	write_coord(origin[1])
	write_coord(origin[2])
	write_coord(iOrigin[0])
	write_coord(iOrigin[1])
	write_coord(iOrigin[2])
	write_short(g_trailSpr)
	write_byte(0)
	write_byte(1) // кадры в 0.1
	write_byte(timeLife) // жизни в 0.1
	write_byte(width) // ширина в 0.1
	write_byte(amplitude) // амплитуда в 0.1
	write_byte(r) // r
	write_byte(g) // g
	write_byte(b) // b
	write_byte(100) // яркость
	write_byte(1) // кадры в 0.1
	message_end()
}

public create_spr_player_point(id, g_trailSpr, width){
    new origin[3]
    get_user_origin(id,origin,0)

    message_begin(MSG_BROADCAST ,SVC_TEMPENTITY,origin,id)
    write_byte(TE_SPRITE)//говорим что хотим создать, в данном случае спрайт
    write_coord(origin[0])//х - координата
    write_coord(origin[1])//у - координата
    write_coord(origin[2])//z - координата
    write_short(g_trailSpr)// id спрайта
    write_byte(width) //масштаб
    write_byte(100)//яркость
    message_end()
}

public create_spr_in_player(id, spr, size){
    new origin[3]
    get_user_origin(id,origin,0)

    message_begin(MSG_BROADCAST ,SVC_TEMPENTITY,origin,id)
    write_byte(TE_SPRITE)//говорим что хотим создать, в данном случае спрайт
    write_coord(origin[0])//х - координата
    write_coord(origin[1])//у - координата
    write_coord(origin[2])//z - координата
    write_short(spr)// id спрайта
    write_byte(size) //масштаб
    write_byte(100)//яркость
    message_end()
}

public create_cycle_spr_in_player(id, timeLife, width, r, g, b, g_trailSpr){
	new radius = 1.0
	new origin[3] = {0,0,0}
	get_entvar(id, var_origin, origin)

	message_begin(MSG_BROADCAST ,SVC_TEMPENTITY,origin,id)
	write_byte(TE_BEAMTORUS)
	engfunc(EngFunc_WriteCoord, origin[0]);
	engfunc(EngFunc_WriteCoord, origin[1]);
	engfunc(EngFunc_WriteCoord, origin[2]);
	engfunc(EngFunc_WriteCoord, origin[0]);
	engfunc(EngFunc_WriteCoord, origin[1]);
	engfunc(EngFunc_WriteCoord, origin[2] + 16.0 + radius * 2);
	write_short(g_trailSpr);
	write_byte(0)
	write_byte(1)
	write_byte(timeLife)
	write_byte(width)
	write_byte(10)
	write_byte(r)
	write_byte(g)
	write_byte(b)
	write_byte(100)
	write_byte(1)
	message_end();
}

public create_trail_spr_after_obj(id, life, width, r, g, b, g_trailSpr){
    message_begin(MSG_BROADCAST, SVC_TEMPENTITY)
    write_byte(TE_BEAMFOLLOW) // TE id
    write_short(id) // entity
    write_short(g_trailSpr) // sprite
    write_byte(life) // life
    write_byte(width) // width
    write_byte(r) // r
    write_byte(g) // g
    write_byte(b) // b
    write_byte(200) // brightness
    message_end()
}

public create_splash_spr_obj(id, spr, count, life, scale, noise, speed){
	//Float:origin[3], const sprite, const cound = 20, const life = 20, const scale = 4, const noise = 20, const speed = 10
	new Float:origin[3];
	get_entvar(id, var_origin, origin);

	message_begin(MSG_BROADCAST, SVC_TEMPENTITY);
	write_byte(TE_SPRITETRAIL);
	write_coord_f(origin[0]);
	write_coord_f(origin[1]);
	write_coord_f(origin[2] + 20.0);
	write_coord_f(origin[0]);
	write_coord_f(origin[1]);
	write_coord_f(origin[2] + 80.0);
	write_short(spr);
	write_byte(count);
	write_byte(life);
	write_byte(scale);
	write_byte(noise);
	write_byte(speed);
	message_end();
}

public create_light_spr_obj(id, radius, r, g, b, life, speed){
	new Float:origin[3];
	get_entvar(id, var_origin, origin);

	message_begin(MSG_BROADCAST,SVC_TEMPENTITY)
	write_byte(TE_DLIGHT) // 27
	write_coord(floatround(origin[0])) // x
	write_coord(floatround(origin[1])) // y
	write_coord(floatround(origin[2])) // z
	write_byte(radius) // radius
	write_byte(r) // Red
	write_byte(g) // Green
	write_byte(b) // Blue
	write_byte(life) // life
	write_byte(speed) // decay rate
	message_end()
}

public drop_weapons(id, dropwhat){
	static weapons[32], num, i, weaponid
	num = 0
	get_user_weapons(id, weapons, num)

	for (i = 0; i < num; i++){
		weaponid = weapons[i]

		if (dropwhat == 1 && ((1<<weaponid) & PRIMARY_WEAPONS_BIT_SUM)){
			static wname[32]
			get_weaponname(weaponid, wname, sizeof wname - 1)
			engclient_cmd(id, "drop", wname)
		}else if (dropwhat == 2 && ((1<<weaponid) & SECONDARY_WEAPONS_BIT_SUM)){
			static wname[32]
			get_weaponname(weaponid, wname, sizeof wname - 1)
			engclient_cmd(id, "drop", wname)
		}
	}
}

public set_gun_model(id, V_Models[], P_Models[]){
	if( !is_user_connected(id) ) return PLUGIN_HANDLED

	set_pev(id, pev_viewmodel2, V_Models)
	set_pev(id, pev_weaponmodel2, P_Models)

	return PLUGIN_HANDLED
}

public UTIL_PlayWeaponAnimation(Player, Sequence){
	set_pev(Player, pev_weaponanim, Sequence)

	message_begin(MSG_ONE_UNRELIABLE, SVC_WEAPONANIM, .player = Player)
	write_byte(Sequence)
	write_byte(2)
	message_end()
}

public give_gun(id, weapon_type){
	switch (weapon_type){
		case 10: {
			drop_weapons(id, 1)
			new iWep2 = give_item(id,"weapon_ak47")
			cs_set_weapon_ammo(iWep2, 30)
			cs_set_user_bpammo (id, CSW_AK47, 90)
			UTIL_PlayWeaponAnimation(id, 2)
			set_pdata_float(id, m_flNextAttack, 1.0, PLAYER_LINUX_XTRA_OFF)
		}
		case 11: {
			drop_weapons(id, 1)
			new iWep2 = give_item(id,"weapon_aug")
			cs_set_weapon_ammo(iWep2, 30)
			cs_set_user_bpammo (id, CSW_AUG, 90)
			UTIL_PlayWeaponAnimation(id, 2)
			set_pdata_float(id, m_flNextAttack, 1.0, PLAYER_LINUX_XTRA_OFF)
		}
		case 12: {
			drop_weapons(id, 1)
			new iWep2 = give_item(id,"weapon_awp")
			cs_set_weapon_ammo(iWep2, 10)
			cs_set_user_bpammo (id, CSW_AWP, 30)
			UTIL_PlayWeaponAnimation(id, 2)
			set_pdata_float(id, m_flNextAttack, 1.0, PLAYER_LINUX_XTRA_OFF)
		}
		case 13: {
			drop_weapons(id, 1)
			new iWep2 = give_item(id,"weapon_m249")
			cs_set_weapon_ammo(iWep2, 100)
			cs_set_user_bpammo (id, CSW_M249, 200)
			UTIL_PlayWeaponAnimation(id, 2)
			set_pdata_float(id, m_flNextAttack, 1.0, PLAYER_LINUX_XTRA_OFF)
		}
		case 20: {
			drop_weapons(id, 2)
			new iWep2 = give_item(id,"weapon_deagle")
			cs_set_weapon_ammo(iWep2, 7)
			cs_set_user_bpammo (id, CSW_DEAGLE, 49)
			UTIL_PlayWeaponAnimation(id, 2)
			set_pdata_float(id, m_flNextAttack, 1.0, PLAYER_LINUX_XTRA_OFF)
		}
	}
	return PLUGIN_HANDLED
}

public combStr(shablon[], str[]){
	static buff[128], iLen
	iLen = 0
	iLen += formatex(buff[iLen], charsmax(buff) - iLen, shablon, str )
	return buff
}



public task_delite_entity(iEntity){ remove_entity(iEntity); }

stock task_change_infEff_to_knife(data[]){
	new const v_knife_model[][] = {
		"models/zm_knifes/v_knife_zm_class_Inv.mdl",
		"models/zm_knifes/v_knife_zm_class_banchee.mdl",
		"models/zm_knifes/v_knife_zm_doctor.mdl",
		"models/zm_knifes/v_knife_zm_class_heavy.mdl",
		"models/zm_knifes/v_knife_zm_class_rev_fire.mdl",
		"models/zm_knifes/v_knife_zm_class_rev_ice.mdl",
		"models/zm_knifes/v_knife_zm_class_spider.mdl",
		"models/zm_knifes/v_knife_zm_class_ksenon.mdl",
		"models/zm_knifes/v_knife_zm_class_rev_void.mdl",
	}

	new id = data[0]
	new zm_id = data[1]

	set_pev(id, pev_viewmodel, engfunc(EngFunc_AllocString, v_knife_model[zm_id] ))
	set_pev(id, pev_weaponmodel, engfunc(EngFunc_AllocString, "" ))
}

stock my_fm_set_rendering(entity, fx, r, g, b, render, amount){
	static Float:color[3]
	color[0] = float(r)
	color[1] = float(g)
	color[2] = float(b)

	set_pev(entity, pev_renderfx, fx)
	set_pev(entity, pev_rendercolor, color)
	set_pev(entity, pev_rendermode, render)
	set_pev(entity, pev_renderamt, float(amount))
	
	return PLUGIN_HANDLED
}

stock Wall1(Float: vecStart[3], Float: vecEnd[3], PlayerEnt)	// для native_draw_into_oneself
{
	static iTrace;iTrace = create_tr2();
	static Float: vecEndPos[3];
	engfunc(EngFunc_TraceLine, vecStart, vecEnd, IGNORE_MONSTERS, PlayerEnt, iTrace);
	get_tr2(iTrace, TR_vecEndPos, vecEndPos);
	free_tr2(iTrace);
	return floatround(get_distance_f(vecEnd, vecEndPos));
}



stock get_speed_vector(const Float:origin1[3],const Float:origin2[3],Float:speed, Float:new_velocity[3])	// для native_draw_into_oneself
{
	new_velocity[0] = origin2[0] - origin1[0]
	new_velocity[1] = origin2[1] - origin1[1]
	new_velocity[2] = origin2[2] - origin1[2]
	new Float:num = floatsqroot(speed*speed / (new_velocity[0]*new_velocity[0] + new_velocity[1]*new_velocity[1] + new_velocity[2]*new_velocity[2]))
	new_velocity[0] *= num
	new_velocity[1] *= num
	new_velocity[2] *= num/1.0
	return 1;
}