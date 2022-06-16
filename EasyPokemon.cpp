#include<bits/stdc++.h> 
#include<ctime>
 
using namespace std;

typedef long long LL;

template<typename SS>

string to_string(SS value)
{
	ostringstream os;
	os << value;
	return os.str();
}

LL string_int(string x)
{
	LL len = x.length(), ret = 0;
	vector<LL> val;
	for (LL i = 0; i < len; ++i)
	{
		if ('0' <= x[i] && x[i] <= '9')
		{
			val.push_back(x[i] - '0');
		}
		else return -1;
	}
	for (LL i = 0; i < val.size(); ++i)
	{
		ret = ret * 10 + val[i];
	}
	return ret;
}

#define hP    1
#define nATK  2
#define nDEF  3
#define sATK  4
#define sDEF  5
#define speed 6

#define MAGIC_SKILL   1
#define PHYSICS_SKILL 2
#define CHANGE_SKILL  3
class SKILL_DATA
{
	private:
		string name, intro;
		LL pp, type, dam, acc, tp, sk_type, C; 
	public:
		void set(LL TP, LL TYPE, LL SK_TYPE, LL DAM, LL ACC, LL PP, LL c, string nm)
		{
			tp = TP; type = TYPE; sk_type = SK_TYPE; dam = DAM; acc = ACC; pp = PP; C = c;
			name = nm;
		}
		void set_intro(string INTRO)
		{
			intro = INTRO;
		}
		void show()
		{
			cout << "SKILL-->" << name << endl;
			cout << intro << endl;
			if (sk_type == 1 || sk_type == 2)
			{
				cout << "  威力：" << dam << endl; 
				cout << "  命中：" << acc << endl; 
			}
			cout << "最大PP：" << pp << endl << endl;
		}
		LL get_pp() { return pp; }
		LL get_type() { return type; }
		LL get_dam() { return dam; }
		LL get_acc() { return acc; }
		LL get_tp() { return tp; }
		LL get_sk_type() { return sk_type; }
		string get_name() { return name; }
		LL get_C() { return C; }
};

SKILL_DATA sk_data[70];

class POKEMON_DATA
{
	private:
		LL exp_type;
		LL type1, type2;
		string name;
		LL str[10];//HP, nATK, nDEF, sATK, sDEF, speed
		LL skill[6];
	public:
		LL get_exp_type() { return exp_type; }
		LL get_type1() { return type1; }
		LL get_type2() { return type2; }
		vector<LL> get_str()
		{
			vector<LL> ret;
			for (LL i = 1; i <= 6; ++i)
			{
				ret.push_back(str[i]);
			}
			return ret;
		}
		vector<LL> get_skill()
		{
			vector<LL> ret;
			for (LL i = 1; i <= 4; ++i)
			{
				ret.push_back(skill[i]);
			}
			return ret;
		}
		string get_name() { return name; }
		void set_SK_STR(vector<LL> SK, vector<LL> STR)
		{
			for (LL i = 0; i < 4; ++i)
			{
				skill[i + 1] = SK[i];
			}
			for (LL i = 0; i < 6; ++i)
			{
				str[i + 1] = STR[i];
			}
		}
		void set_data(string nm, LL ET = 1, LL T1 = 0, LL T2 = 0)
		{
			exp_type = ET; type1 = T1; type2 = T2;
			name = nm;
			memset(skill, 0, sizeof(skill));
			memset(str, 0, sizeof(str));
		}
		void show()
		{
			cout << name << endl;
			cout << "种族值----------->" << endl;
			cout << "体力: " << str[hP] << endl;
			cout << "攻击: " << str[nATK] << endl;
			cout << "特攻: " << str[sATK] << endl;
			cout << "防御: " << str[nDEF] << endl;
			cout << "特防: " << str[sDEF] << endl;
			cout << "速度: " << str[speed] << endl << endl;
			cout << "技能------------->" << endl; 
			for (LL i = 1; i <= 4; ++i)
			{
				sk_data[skill[i]].show();
			}
		}
};

LL exp_upp[105][10];
LL B[120];
double Abi_Time[20];
double type_cross[32][32]; //[atk][def]
POKEMON_DATA pm_data[32];
string Status_Name[32], Type_Name[32];

void Load_ExpUpperBound()
{
	ifstream in("ExpUpperBound.txt");
	for (LL i = 1; i <= 99; ++i)
	{
		for (LL j = 1; j <= 6; ++j)
		{
			in >> exp_upp[i][j];
		}
	}
	in.close();
}

void Load_TypeCross()
{
	ifstream in("TypeCross.txt");
	for (LL i = 1; i <= 18; ++i)
	{
		for (LL j = 1; j <= 18; ++j)
		{
			in >> type_cross[i][j];
		}
	}
	fclose(stdin);
}

void Load_Pokemon_Information()
{
	ifstream in("Pokemon_Information.txt");
	string Pm_name;
	LL t1, t2, expt;
	vector<LL> ski, stri;
	for (LL i = 1; i <= 22; ++i)
	{
		ski.clear();
		stri.clear();
		in >> Pm_name >> t1 >> t2 >> expt;
		for (LL j = 1; j <= 6; ++j)
		{
			LL x; in >> x;
			stri.push_back(x);
		}
		cout << endl;
		for (LL j = 1; j <= 4; ++j)
		{
			LL x; in >> x;
			ski.push_back(x);
		}
		cout << endl;
		pm_data[i].set_data(Pm_name, expt, t1, t2);
		pm_data[i].set_SK_STR(ski, stri);
	}
	in.close();
}

void Load_B()
{
	ifstream in("B.txt");
	for (LL i = 1; i <= 10; ++i)
	{
		LL x, y; in >> x >> y;
		B[x] = y;
	}
	in.close();
}

void Load_Ability_Change()
{
	ifstream in("Ability_Change.txt");
	for (LL i = 0; i < 13; ++i)
	{
		LL x; in >> x;
		Abi_Time[i] = x;
	}
	in.close();
}

void Load_Skill()
{
	ifstream in("Skill_Information.txt");
	for (LL i = 1; i <= 51; ++i)
	{
		LL id, tp, d, p, ty, cc, sk_type, Acc;
		string NAME;
		in >> id >> tp;
		in >> NAME;
		in >> ty >> sk_type >> d >> Acc >> p >> cc;
		sk_data[id].set(tp, ty, sk_type, d, Acc, p, cc, NAME);
	}
	in.close();
}

void Load_StatusName()
{
	ifstream in("StatusName.txt");
	for (LL i = 1; i <= 14; ++i)
	{
		in >> Status_Name[i];
	}
	in.close();
}

void Load_TypeName()
{
	ifstream in("TypeName.txt");
	for (LL i = 1; i <= 18; ++i)
	{
		in >> Type_Name[i];
	}
	in.close();
}

void Load_Skill_Detail()
{
	ifstream in("SkillDetail.txt");
	for (LL i = 1; i <= 51; ++i)
	{
		LL id; string detail;
		in >> id >> detail;
		sk_data[id].set_intro(detail);
	}
	in.close();
}

void Init()
{
	cout << "Loading Files..." << endl;
	Load_ExpUpperBound();
	Load_TypeCross(); 
	Load_Pokemon_Information();
	Load_B(); 
	Load_Ability_Change();
	Load_Skill(); 
	Load_StatusName();
	Load_TypeName();
	Load_Skill_Detail();
}

class POKEMON
{
	private:
		LL id, lv, exp;
	public:
		POKEMON(LL ID, LL LV, LL EXP): id(ID), lv(LV), exp(EXP) {};
		void set(LL ID, LL LV, LL EXP)
		{
			id = ID; lv = LV; exp = EXP;
		}
		void show() 
		{
			cout << "ID: " << id << endl;
			pm_data[id].show(); 
			cout << "Lv." << lv << endl;
			cout << "EXP: " << exp << "/" << exp_upp[lv][pm_data[id].get_exp_type()] << endl;
		}
		LL get_LV() { return lv; }
		LL get_ID() { return id; }
		LL get_EXP() { return exp; }
		bool operator < (const POKEMON &A) const
		{
			return lv > A.lv; 
		}
		void set_exp(LL EXP)
		{
			exp += EXP;
			while (exp >= exp_upp[lv][pm_data[id].get_exp_type()])
			{
				exp -= exp_upp[lv][pm_data[id].get_exp_type()];
				++lv;
			}
		}
};

class PM_Battle: public POKEMON
{
	private:
		LL HP, NATK, SATK, NDEF, SDEF, SPEED, resHP;
	public:
		LL pp[6], status[30];
		PM_Battle(LL ID, LL LV, LL EXP): POKEMON(ID, LV, EXP)
		{
			vector<LL> str_data = pm_data[ID].get_str();
			HP = ((str_data[0] * 2 + 31) * LV) / 100 + 10 + LV;
			NATK = ((str_data[1] * 2 + 31) * LV) / 100 + 5;
			NDEF = ((str_data[2] * 2 + 31) * LV) / 100 + 5;
			SATK = ((str_data[3] * 2 + 31) * LV) / 100 + 5;
			SDEF = ((str_data[4] * 2 + 31) * LV) / 100 + 5;
			SPEED = ((str_data[5] * 2 + 31) * LV) / 100 + 5;
			vector<LL> skill_data = pm_data[ID].get_skill();
			for (LL i = 1; i <= 4; ++i)
			{
				pp[i] = sk_data[skill_data[i - 1]].get_pp();
			}
			memset(status, 0, sizeof(status));
			resHP = HP;
		}
		LL get_HP() { return HP; }
		LL get_NATK() { return NATK; }
		LL get_NDEF() { return NDEF; }
		LL get_SATK() { return SATK; }
		LL get_SDEF() { return SDEF; }
		LL get_SPEED() { return SPEED; }
		LL get_resHP() { return resHP; }
		void Give_Damage(LL DAM)
		{
			resHP = max(0ll, resHP - DAM);
		}
		void Cure(LL NUM)
		{
			resHP = max(HP, resHP + NUM);
		}
};

LL SaveID, stone, pm_ammount, free_exp;
LL Year, Month, Day, Hour, Minute, Second;
vector<POKEMON> pm;
LL value_exp[7] = {0, 1000, 3000, 7000, 12000, 18000, 25000};

class Saving
{
	public:
		Saving() {}
		void Save_Data(LL Y, LL M1, LL D, LL H, LL M2, LL S, LL num)
		{
			out << pm_ammount << " " << Y << " " << M1 << " " << D << " " << H << " " << M2 << " " << S << endl;
			out << stone << " " << free_exp << endl;
			for (LL i = 0; i < pm_ammount; ++i)
			{
				out << pm[i].get_ID() << " " << pm[i].get_LV() << " " << pm[i].get_EXP() << endl;
			}
			out.close();
		}
		void Load_File(LL num)
		{
			
			SaveID = num;
			if (num == 1) ifstream in("Save1.txt");
			else if (num == 2) ifstream in("Save2.txt");
			else ifstream in("Save3.txt");
			in >> pm_ammount;
			if (pm_ammount == -1)
			{
				POKEMON tmp(21, 50, 0);
				pm.push_back(tmp); pm_ammount = 1;
			}
			else
			{
				in >> Year >> Month >> Day >> Hour >> Minute >> Second;
				in >> stone >> free_exp;
				pm.clear();
				for (LL i = 1; i <= pm_ammount; ++i)
				{
					LL pm_id, pm_lv, pm_exp;
					in >> pm_id >> pm_lv >> pm_exp;
					POKEMON tmp(pm_id, pm_lv, pm_exp);
					pm.push_back(tmp);
				}
			}
			sort(pm.begin(), pm.end());
			in.close();
			Game_Menu(); 
		}
		void Delete_File(LL num)
		{
			if (num == 1) ofstream out("Save1.txt");
			else if (num == 2) ofstream out("Save2.txt");
			else ofstream out("Save3.txt");
			out << "-1";
			out.close();
		}
		virtual void Save_Data_Direct(LL Y, LL M1, LL D, LL H, LL M2, LL S) = 0;
		virtual void Load_File_Direct() = 0;
		virtual void Delete_File_Direct() = 0;
};

class Saving1: public Saving
{
	public:
		void Save_Data_Direct(LL Y, LL M1, LL D, LL H, LL M2, LL S)
		{
			Save_Data_Direct(Y, M1, D, H, M2, S, 1);
		}
		void Load_File_Direct()
		{
			Load_File(1);
		}
		void Delete_File_Direct()
		{
			Delete_File(1);
		}
};

class Saving2: public Saving
{
	public:
		void Save_Data(LL Y, LL M1, LL D, LL H, LL M2, LL S)
		{
			Save_Data_Direct(Y, M1, D, H, M2, S, 2);
		}
		void Load_File()
		{
			Load_File(2);
		}
		void Delete_File_Direct()
		{
			Delete_File(2);
		}
};

class Saving3: public Saving
{
	public:
		void Save_Data(LL Y, LL M1, LL D, LL H, LL M2, LL S)
		{
			Save_Data_Direct(Y, M1, D, H, M2, S, 3);
		}
		void Load_File()
		{
			Load_File(3);
		}
		void Delete_File_Direct()
		{
			Delete_File(3);
		}
};

void Game_Menu();
void Title();

void MenuGroup(string s1, string s2)
{
	cout.setf(ios::left);
	cout.width(25);
	cout.fill(' ');
	cout << s1 << endl;
	cout.unsetf(ios::left);
	
	cout.setf(ios::right);
	cout.width(25);
	cout.fill(' ');
	cout << s2 << endl;
	cout.unsetf(ios::right);
	cout << "-------------------------" << endl;
}

LL Choose_Pokemon(LL Elv, LL Eid)
{
	system("cls");
	cout << "本次对战的对手是 Lv." << Elv << " " << pm_data[Eid].get_name() << endl << endl;
	cout << "请选择出战的宝可梦：" << endl;
	cout << "-------------------------" << endl;
	for (LL i = 0; i < pm_ammount; ++i)
	{
		MenuGroup(to_string(i + 1) + "." + pm_data[pm[i].get_ID()].get_name(), "Lv." + to_string(pm[i].get_LV()));
	}
	cout << "输入挑战编号以开始对战。" << endl;
	cout << "输入其他内容以退出挑战页面。" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "Option: ";
	string OP; cin >> OP; 
	LL ans = string_int(OP);
	if (1 <= ans && ans <= pm_ammount) return ans - 1;
	else return -1;
}

void cout_myHP(PM_Battle my)
{
	cout << "HP: " << my.get_resHP() << " / " << my.get_HP() << endl;
}

void cout_enHP(PM_Battle en)
{
	double per = (double)en.get_resHP() / (double)en.get_HP() * 100.0;
	printf("HP: %.2lf", per); cout << "%" << endl;
}

void print_SKILL(PM_Battle my)
{
	vector<LL> my_skill = pm_data[my.get_ID()].get_skill();
	cout << "-------------------------" << endl;
	for (LL i = 0; i <= 3; ++i)
	{
		string detail;
		if (sk_data[my_skill[i]].get_sk_type() == 1 || sk_data[my_skill[i]].get_sk_type() == 2)
		{
			detail = "威力 " + to_string(sk_data[my_skill[i]].get_dam()) + 
					 "  PP " + to_string(my.pp[i + 1]) + " / " + to_string(sk_data[my_skill[i]].get_pp());
		}
		else detail = "PP " + to_string(my.pp[i + 1]) + " / " + to_string(sk_data[my_skill[i]].get_pp());
		MenuGroup(to_string(i + 1) + "." + sk_data[my_skill[i]].get_name(), detail);
	}
}

void Battle_Output(PM_Battle my, PM_Battle en, string word)
{
	LL myID = my.get_ID(), enID = en.get_ID();
	system("cls");
	cout.setf(ios::left);
	cout.width(50); cout << "My Pokemon"; cout << "Enemy Pokemon" << endl;
	cout.width(50); cout << pm_data[myID].get_name(); cout << pm_data[enID].get_name() << endl;
	cout.width(50); cout << "Lv." + to_string(my.get_LV()); cout << "Lv." + to_string(en.get_LV()) << endl;
	cout.width(50); cout << "HP: " + to_string(my.get_resHP()) + " / " + to_string(my.get_HP());
	cout_enHP(en);
	LL ok = 0;
	for (LL i = 1; i <= 4; ++i)
	{
		if (my.status[i] > 0) { cout.width(50); cout << Status_Name[i]; ok = 1; break; }
	}
	if (!ok) { cout.width(50); cout << " "; }
	for (LL i = 1; i <= 4; ++i)
	{
		if (en.status[i] > 0) { cout << Status_Name[i]; break; }
	}
	cout << endl;
	
	vector<pair<LL, LL> > my_status, en_status;
	for (LL i = 10; i <= 14; ++i)
	{
		if (my.status[i] != 0) my_status.push_back(make_pair(i, my.status[i]));
		if (en.status[i] != 0) en_status.push_back(make_pair(i, en.status[i]));
	}
	for (LL i = 0; i <= 4; ++i)
	{
		cout.width(50);
		if (i < my_status.size())
		{
			LL x = my_status[i].first, y = my_status[i].second;
			cout << Status_Name[x] + "：" + to_string(y); 
		}
		else cout << " ";
		if (i < en_status.size())
		{
			LL a = en_status[i].first, b = en_status[i].second;
			cout << Status_Name[a] + "：" + to_string(b); 
		}
		cout << endl;
	}
	cout.width(21); cout << " ";
	if (my.status[5] > 0) cout << "天气：下雨";
	cout << endl; 
	cout << "----------------------------------------------" << endl;
	cout << word << endl;
	LL c1 = clock();
	while (1)
	{
		if (clock() - c1 > 1500) break;
	}
}

void Before_Battle(PM_Battle my, PM_Battle en)
{
	LL myID = my.get_ID(), enID = en.get_ID();
	system("cls");
	
	cout.width(50); cout.setf(ios::right);
	cout << "Enemy Pokemon:" << endl;
	cout.width(50);
	cout << pm_data[enID].get_name() + " Lv." + to_string(en.get_LV()) << endl;
	cout.width(50);
	cout << "HP: 100%" << endl;
	cout.unsetf(ios::right);
	
	cout << endl;
	cout << "                  *    *   *****" << endl;
	cout << "                  *    *  *     " << endl;
	cout << "                  *   *   ***** " << endl;
	cout << "                   * *        * " << endl;
	cout << "                    *    *****  " << endl; 
	cout << endl; 

	cout.setf(ios::left);
	cout.width(50);
	cout.fill(' ');
	cout << "My Pokemon: " << endl
	     << pm_data[myID].get_name() << " Lv." << my.get_LV() << endl;
	cout_myHP(my);
	cout.unsetf(ios::left);
	
	LL c1 = clock();
	while (1)
	{
		if (clock() - c1 > 3000) break;
	}
}

LL check_not_finish(PM_Battle my, PM_Battle en)
{
	if (my.get_resHP() == 0)
	{
		Battle_Output(my, en, pm_data[my.get_ID()].get_name() + "倒下了！");
		return -1;
	}
	if (en.get_resHP() == 0)
	{
		Battle_Output(my, en, pm_data[en.get_ID()].get_name() + "倒下了！");
		return 1;
	} 
	LL ok1 = 0, ok2 = 0;
	for (LL i = 1; i <= 4; ++i)
	{
		if (en.pp[i] > 0) { ok2 = 1; break; }
	}
	for (LL i = 1; i <= 4; ++i)
	{
		if (my.pp[i] > 0) { ok1 = 1; break; }
	}
	if (ok2 == 0)
	{
		Battle_Output(my, en, pm_data[en.get_ID()].get_name() + "没有可以使用的招式了！");
		return 1; 
	}
	else if (ok1 == 0)
	{
		Battle_Output(my, en, pm_data[my.get_ID()].get_name() + "没有可以使用的招式了！");
		return -1;
	}
	return 0;
}

LL Check_use_succ(PM_Battle pm2, LL S)
{
	LL acc = sk_data[S].get_acc();
	if (acc == -1) return 1;
	LL b = B[acc];
	LL A = rand() % 255 + 1;
	if (A <= b) return 1; 
	else return 0;
}

LL p(LL x)
{
	LL A = rand() % 100 + 1;
	if (A <= x) return 1;
	else return 0;
}

bool no_4status(PM_Battle def)
{
	if (def.status[1] || def.status[2] || def.status[3] || def.status[4]) return 0;
	else return 1;
}

void Skill_Effect(PM_Battle &atk, PM_Battle &def, LL S, LL rev, LL lstS)
{
	string atk_name = pm_data[atk.get_ID()].get_name(), def_name = pm_data[def.get_ID()].get_name();
	LL DAM = sk_data[S].get_dam(); 
	LL natk = atk.get_NATK(), satk = atk.get_SATK(), ndef = def.get_NDEF(), sdef = def.get_SDEF();
	LL atk_speed = atk.get_SPEED(), def_speed = def.get_SPEED();
	LL atk_hp = atk.get_HP(), atk_reshp = atk.get_resHP();
	LL atk_lv = atk.get_LV(), def_lv = def.get_LV();
	LL atk_t1 = pm_data[atk.get_ID()].get_type1(), atk_t2 = pm_data[atk.get_ID()].get_type2();
	LL def_t1 = pm_data[def.get_ID()].get_type1(), def_t2 = pm_data[def.get_ID()].get_type2();
	LL skill_type = sk_data[S].get_sk_type(); LL skill_ele_type = sk_data[S].get_type();
	if (atk.status[3] > 0)
	{
		if (rev) Battle_Output(def, atk, atk_name + "睡得很香甜");
		else Battle_Output(atk, def, atk_name + "睡得很香甜");
		return;
	}
	if (atk.status[7] > 0)
	{
		if (rev) Battle_Output(def, atk, atk_name + "无法行动");
		else Battle_Output(atk, def, atk_name + "无法行动");
		return; 
	}
	if (atk.status[2] > 0) 
	{
		LL A = rand() % 100 + 1;
		if (A <= 25)
		{
			if (rev) Battle_Output(def, atk, atk_name + "因为麻痹而动弹不得");
			else Battle_Output(atk, def, atk_name + "因为麻痹而动弹不得");
			return; 
		}
		atk_speed /= 2;
	}
	if (atk.status[6] > 0)
	{
		if (rev) Battle_Output(def, atk, atk_name + "畏缩了，不敢行动。");
		else Battle_Output(atk, def, atk_name + "畏缩了，不敢行动。");
		return; 
	}
	if (rev) Battle_Output(def, atk, atk_name + "使用了" + sk_data[S].get_name());
	else Battle_Output(atk, def, atk_name + "使用了" + sk_data[S].get_name());
	//制裁光砾 属性赋值
	if (S == 51)
	{
		skill_ele_type = rand() % 18 + 1; 
		if (rev) Battle_Output(def, atk, "制裁光砾获得了" + Type_Name[skill_ele_type] + "属性");
		else Battle_Output(atk, def, atk_name + "制裁光砾获得了" + Type_Name[skill_ele_type] + "属性");
	}
	//pp-1
	vector<LL> SS = pm_data[atk.get_ID()].get_skill(); LL pp_pos = 0;
	for (LL i = 1; i <= 4; ++i)
	{
		if (S == SS[i - 1])
		{
			pp_pos = i; break;
		}
	}
	--atk.pp[pp_pos];
	//查询是否命中 
	LL succ = Check_use_succ(atk, S);
	//食梦对未进入睡眠状态的宝可梦使用、电磁波对地面属性宝可梦使用会使用失败
	if ((S == 22 && def.status[3] == 0) || (S == 7 && (def_t1 == 5 || def_t2 == 5)))
	{
		if (rev) Battle_Output(def, atk, "攻击没有效果！");
		else Battle_Output(atk, def, "攻击没有效果！");
		return; 
	}
	//暴风 下雨时必定命中 
	if (S == 21 && atk.status[5] > 0) succ = 1;
	//打雷 下雨时必定命中 
	if (S == 54 && atk.status[5] > 0) succ = 1;
	if (!succ)
	{
		if (rev) Battle_Output(def, atk, "攻击没有命中！");
		else Battle_Output(atk, def, "攻击没有命中！");
		return; 
	}
	if (def.status[2] > 0) def_speed /= 2;
	
	if (atk.status[5] > 0)
	{
		if (skill_ele_type == 10) DAM /= 2;
		if (skill_ele_type == 11) DAM = (LL)((double)DAM * 1.5); 
		if (S == 11)
		{
			if (rev) Battle_Output(def, atk, "已经在下雨了！");
			else Battle_Output(atk, def, "已经在下雨了！");
			return;
		}
	}
	if (atk.status[8] > 0 && S == 32)
	{
		if (rev) Battle_Output(def, atk, "水流环无法叠加了。");
		else Battle_Output(atk, def, "水流环无法叠加了。");
		return; 
	}
	//能力修正
	natk = (double)natk * Abi_Time[atk.status[10] + 6];
	satk = (double)satk * Abi_Time[atk.status[11] + 6];
	ndef = (double)ndef * Abi_Time[def.status[12] + 6];
	sdef = (double)sdef * Abi_Time[def.status[13] + 6];
	atk_speed = (double)atk_speed * Abi_Time[atk.status[14] + 6];
	def_speed = (double)def_speed * Abi_Time[def.status[14] + 6];
	 
	//计算是否击中要害
	double bonus = 1 + 0.5 * ((sk_data[S].get_C() == 1) ? p(13) : p(7));
	if (bonus > 1)
	{
		if (rev) Battle_Output(def, atk, "击中了要害！");
		else Battle_Output(atk, def, "击中了要害！");
	}
	//是否有属性一致伤害加成 
	bonus *= ((skill_ele_type == atk_t1 || skill_ele_type == atk_t2) ? 1.5 : 1);
	//属性相克倍率
	double typeTime = type_cross[skill_ele_type][def_t1];
	if (def_t2 != 0) typeTime *= type_cross[skill_ele_type][def_t2];
	bonus *= typeTime;
	//随机数
	bonus *= ((double)(85 + rand() % 16) / 100.0);
	//光子喷涌 技能类型修正 
	if (S == 45 && natk > satk) skill_type = 2;
	//电球 威力修正
	if (S == 6)
	{
		double per = (double)atk_speed / (double)def_speed;
		if (0 <= per && per < 1) DAM = 40;
		else if (1 <= per && per < 2) DAM = 60;
		else if (2 <= per && per < 3) DAM = 80;
		else if (3 <= per && per < 4) DAM = 120;
		else DAM = 150;
	}
	//喷水/喷火 威力修正
	if (S == 9 || S == 18) DAM = 150 * (double)(atk_reshp / atk_hp);
	//交错闪电/交错火焰 威力修正
	if (S == 34 && lstS == 36) DAM *= 2;
	if (S == 36 && lstS == 34) DAM *= 2; 
	//以牙还牙 威力修正
	if (S == 47 && lstS != 0) DAM *= 2;
	//计算伤害量
	double damage = 0.0;
	if (skill_type == 1) damage = max(1.0, ((double)(2 * atk_lv + 10) / 250.0 * ((double)satk / (double)sdef) * DAM + 2) * bonus);
	else if (skill_type == 2) damage = max(1.0, ((2 * atk_lv + 10) / 250 * (natk / ndef) * DAM + 2) * bonus);
	//灼伤对物理攻击伤害修正
	if (atk.status[1] > 0 && skill_type == 2) damage = max(damage / 2.0, 1.0); 
	
	//给予伤害
	if (skill_type == 1 || skill_type == 2) 
	{
		def.Give_Damage((LL)damage);
		if (typeTime <= 0.5)
		{
			if (rev) Battle_Output(def, atk, "看起来效果不是很好...");
			else Battle_Output(atk, def, "看起来效果不是很好...");
		}
		else if (typeTime >= 2)
		{
			if (rev) Battle_Output(def, atk, "效果绝佳！");
			else Battle_Output(atk, def, "效果绝佳！");
		}
	}
	
	//附加效果
	//附加灼伤、麻痹、睡眠、中毒效果
	if (no_4status(def))
	{
		//灼伤
		if ((S == 2 && p(10)) || (S == 13 && p(30)) || (S == 33 && p(20)))
		{
			if (rev) Battle_Output(def, atk, def_name + "灼伤了！");
			else Battle_Output(atk, def, def_name + "灼伤了！");
			def.status[1] = 1;
		}
		//麻痹
		if ((S == 7) || (S == 35 && p(20)) || (S == 53 && p(10)) || (S == 54 && p(30)))
		{
			if (rev) Battle_Output(def, atk, def_name + "麻痹了！");
			else Battle_Output(atk, def, def_name + "麻痹了！");
			def.status[2] = 1;
		}
		//睡眠
		if (S == 23)
		{
			if (rev) Battle_Output(def, atk, def_name + "进入了梦乡。");
			else Battle_Output(atk, def, def_name + "进入了梦乡。");
			def.status[2] = rand() % 3 + 1;
		}
		//中毒
		if (S == 49 && p(30))
		{
			if (rev) Battle_Output(def, atk, def_name + "中毒了！");
			else Battle_Output(atk, def, def_name + "中毒了！");
			def.status[4] = 1;
		}
	}
	//无法行动
	if (S == 46 || S == 48 || S == 26 || S == 50)
	{
		if (rev) Battle_Output(def, atk, atk_name + "下一回合无法行动。");
		else Battle_Output(atk, def, atk_name + "下一回合无法行动。");
		atk.status[7] = 2;
	}
	//下雨
	if (S == 11)
	{
		if (rev) Battle_Output(def, atk, "开始下雨了。");
		else Battle_Output(atk, def, "开始下雨了。");
		def.status[5] = atk.status[5] = 5;
	}
	//水流环
	if (S == 32)
	{
		if (rev) Battle_Output(def, atk, atk_name + "周围覆盖着用水制造的幕。");
		else Battle_Output(atk, def, atk_name + "周围覆盖着用水制造的幕。");
		atk.status[8] = 1; 
	}
	//大地掌控
	if (S == 38)
	{
		if (rev) Battle_Output(def, atk, atk_name + "正在积蓄力量。");
		else Battle_Output(atk, def, atk_name + "正在积蓄力量。");
		atk.status[9] = 2; 
	}
	//畏缩
	if (S == 24 && lstS == 0 && p(20))
	{
		if (rev) Battle_Output(def, atk, def_name + "畏缩了！");
		else Battle_Output(atk, def, def_name + "畏缩了！");
		def.status[6] = 1;
	}
	
	//能力变化
	//攻击
	if (atk.status[10] < 6)
	{
		if (S == 19 || S == 52)
		{
			++atk.status[10];
			if (rev) Battle_Output(def, atk, atk_name + "的攻击提高了！");
			else Battle_Output(atk, def, atk_name + "的攻击提高了！");
		}
	}
	//特攻
	if (def.status[11] > -6)
	{
		if (S == 37 && p(30))
		{
			--def.status[11];
			if (rev) Battle_Output(def, atk, def_name + "的特攻降低了！");
			else Battle_Output(atk, def, def_name + "的特攻降低了！");
		}
	}
	if (atk.status[11] > -6)
	{
		if (S == 17 || S == 31)
		{
			atk.status[11] = max(-6ll, atk.status[11] - 2);
			if (rev) Battle_Output(def, atk, atk_name + "的特攻大幅降低了！");
			else Battle_Output(atk, def, atk_name + "的特攻大幅降低了！");
		}
	}
	if (atk.status[11] < 6)
	{
		if (S == 52)
		{
			++atk.status[11];
			if (rev) Battle_Output(def, atk, atk_name + "的特攻提高了！");
			else Battle_Output(atk, def, atk_name + "的特攻提高了！");
		}
		if (S == 25)
		{
			atk.status[11] = min(6ll, atk.status[11] + 2);
			if (rev) Battle_Output(def, atk, atk_name + "的特攻大幅提高了！");
			else Battle_Output(atk, def, atk_name + "的特攻大幅提高了！");
		}
	}
	//防御
	if (def.status[12] > -6)
	{
		if (S == 27 && p(30))
		{
			--def.status[12];
			if (rev) Battle_Output(def, atk, def_name + "的防御降低了！");
			else Battle_Output(atk, def, def_name + "的防御降低了！");
		}
	}
	if (atk.status[12] < 6)
	{
		if (S == 43)
		{
			++atk.status[12];
			if (rev) Battle_Output(def, atk, atk_name + "的防御提高了！");
			else Battle_Output(atk, def, atk_name + "的防御提高了！");
		}
		if (S == 28)
		{
			atk.status[12] = min(6ll, atk.status[12] + 2);
			if (rev) Battle_Output(def, atk, atk_name + "的防御大幅提高了！");
			else Battle_Output(atk, def, atk_name + "的防御大幅提高了！");
		}
	}
	//特防
	if (def.status[13] > -6)
	{
		if (S == 4 && p(10))
		{
			--def.status[13];
			if (rev) Battle_Output(def, atk, def_name + "的特防降低了！");
			else Battle_Output(atk, def, def_name + "的特防降低了！");
		}
	}
	if (atk.status[13] < 6)
	{
		if (S == 43)
		{
			++atk.status[13];
			if (rev) Battle_Output(def, atk, atk_name + "的特防提高了！");
			else Battle_Output(atk, def, atk_name + "的特防提高了！");
		}
		if (S == 3)
		{
			atk.status[13] = min(6ll, atk.status[13] + 2);
			if (rev) Battle_Output(def, atk, atk_name + "的特防大幅提高了！");
			else Battle_Output(atk, def, atk_name + "的特防大幅提高了！");
		}
	}
	//速度
	if (atk.status[14] < 6)
	{
		if (S == 19)
		{
			++atk.status[14];
			if (rev) Battle_Output(def, atk, atk_name + "的速度大高了！");
			else Battle_Output(atk, def, atk_name + "的速度提高了！");
		}
		if (S == 8)
		{
			atk.status[14] = min(6ll, atk.status[14] + 2);
			if (rev) Battle_Output(def, atk, atk_name + "的速度大幅提高了！");
			else Battle_Output(atk, def, atk_name + "的速度大幅提高了！");
		}
	}
	
	else if (S == 22) atk.Cure((LL)(damage * 0.5));
	else if (S == 26) atk.status[7] = 2;
	else if (S == 27 && p(30) && def.status[12] > -6)
	{
		--def.status[12];
		if (rev) Battle_Output(def, atk, atk_name + "的防御降低了！");
		else Battle_Output(atk, def, atk_name + "的防御降低了！");
	}
	else if (S == 40) atk.Cure((LL)(damage * 0.75));
	else if (S == 42) atk.Give_Damage((LL)((double)atk_hp * 0.5));
}

void Status_Clear(PM_Battle &my, PM_Battle &en)
{
	string my_name = pm_data[my.get_ID()].get_name();
	string en_name = pm_data[en.get_ID()].get_name();
	if (my.status[1] > 0) 
	{
		my.Give_Damage((LL)(max(1.0, (double)my.get_HP() * 0.0625)));
		Battle_Output(my, en, my_name + "因为灼伤受到了伤害。");
	}
	if (en.status[1] > 0)
	{
		en.Give_Damage((LL)(max(1.0, (double)en.get_HP() * 0.0625)));
		Battle_Output(my, en, en_name + "因为灼伤受到了伤害。");
	}
	if (my.status[3] > 0)
	{
		--my.status[3];
		if (!my.status[3]) Battle_Output(my, en, my_name + "醒了！");
	}
	if (en.status[3] > 0)
	{
		--en.status[3];
		if (!en.status[3]) Battle_Output(my, en, en_name + "醒了！");
	}
	if (my.status[4] > 0) 
	{
		my.Give_Damage((LL)(max(1.0, (double)my.get_HP() * 0.125)));
		Battle_Output(my, en, my_name + "因为中毒受到了伤害。");
	}
	if (en.status[4] > 0)
	{
		en.Give_Damage((LL)(max(1.0, (double)en.get_HP() * 0.125)));
		Battle_Output(my, en, en_name + "因为中毒受到了伤害。");
	}
	if (my.status[5] > 0)
	{
		--my.status[5]; --en.status[5];
		if (my.status[5] > 0) Battle_Output(my, en, "仍然在下雨。");
		else Battle_Output(my, en, "雨停了！");
	}
	if (my.status[6] > 0) my.status[6] = 0;
	if (en.status[6] > 0) en.status[6] = 0;
	if (my.status[7] > 0) my.status[7]--;
	if (en.status[7] > 0) en.status[7]--;
	if (my.status[8] > 0)
	{
		my.Cure((LL)(max(1.0, (double)my.get_HP() * 0.0625)));
		Battle_Output(my, en, my_name + "得到了水流环的滋养，回复了一些体力。");
	}
	if (en.status[8] > 0)
	{
		en.Cure((LL)(max(1.0, (double)en.get_HP() * 0.0625)));
		Battle_Output(my, en, en_name + "得到了水流环的滋养，回复了一些HP。");
	}
	if (my.status[9] > 0)
	{
		--my.status[9];
		if (my.status[9] == 0)
		{
			Battle_Output(my, en, my_name + "掌控了大地！");
			my.status[11] = min(6ll, my.status[11] + 2);
			Battle_Output(my, en, my_name + "的特攻大幅提高了！");
			my.status[13] = min(6ll, my.status[13] + 2);
			Battle_Output(my, en, my_name + "的特防大幅提高了！");
			my.status[14] = min(6ll, my.status[14] + 2);
			Battle_Output(my, en, my_name + "的速度大幅提高了！");
		}
		else Battle_Output(my, en, my_name + "正在积蓄力量。");
	}
	if (en.status[9] > 0)
	{
		--en.status[9];
		if (en.status[9] == 0)
		{
			Battle_Output(my, en, en_name + "掌控了大地！");
			en.status[11] = min(6ll, en.status[11] + 2);
			Battle_Output(my, en, en_name + "的特攻大幅提高了！");
			en.status[13] = min(6ll, en.status[13] + 2);
			Battle_Output(my, en, en_name + "的特防大幅提高了！");
			en.status[14] = min(6ll, en.status[14] + 2);
			Battle_Output(my, en, en_name + "的速度大幅提高了！");
		}
		else Battle_Output(my, en, en_name + "正在积蓄力量。");
	}
}

void Use_Skill(PM_Battle &my, PM_Battle &en, LL myS, LL enS)
{
	string my_name = pm_data[my.get_ID()].get_name(), en_name = pm_data[en.get_ID()].get_name();
	LL mySpeed = my.get_SPEED(), enSpeed = en.get_SPEED();
	mySpeed *= Abi_Time[my.status[14] + 6];
	enSpeed *= Abi_Time[en.status[14] + 6];
	if (my.status[2] > 0) mySpeed /= 2;
	if (en.status[2] > 0) enSpeed /= 2;//麻痹->速度减半
	
	if (mySpeed >= enSpeed)
	{
		Skill_Effect(my, en, myS, 0, 0);
		if (en.get_resHP() == 0) return;
		Skill_Effect(en, my, enS, 1, myS);
		if (my.get_resHP() == 0) return;
	}
	else
	{
		Skill_Effect(en, my, enS, 1, 0);
		if (my.get_resHP() == 0) return;
		Skill_Effect(my, en, myS, 0, enS);
		if (en.get_resHP() == 0) return;
	}
	Status_Clear(my, en);
}

void Win_Get_EXP(LL L, LL mID)
{
	LL pos = 0;
	for (LL i = 0; i < pm_ammount; ++i)
	{
		if (pm[i].get_ID() == mID)
		{
			pos = i;
			break;
		}
	}
	LL Lp = pm[pos].get_LV();
	double Exp_Gain = (((310.0 * (double)L) / 5.0) * pow((double)(2.0 * L + 10.0) / (double)(L + Lp + 10.0), 2.5) + 1.0);
	system("cls");
	cout << endl;
	cout << "           *   *   *****  *   *   *" << endl;
	cout << "           *   *     *    **  *   *" << endl;
	cout << "           * * *     *    * * *   *" << endl;
	cout << "           * * *     *    *  **" << endl;
	cout << "            * *    *****  *   *   *" << endl; 
	cout << endl << endl << endl;
	LL Exp = pm[pos].get_EXP();
	cout.width(30); cout << " ";
	cout << pm_data[mID].get_name() + "获得经验值：" << Exp_Gain << endl << endl;
	cout.width(30); cout << " ";
	cout << "ORIGIN INFO: " << "Lv." << Lp << "  EXP: " << Exp << endl;
	pm[pos].set_exp(Exp_Gain);
	Lp = pm[pos].get_LV(); Exp = pm[pos].get_EXP();
	cout.width(30); cout << " ";
	cout << "  CHANGE TO: " << "Lv." << Lp << "  EXP: " << Exp << endl;
	cout << "-------------------------------------------------";
	cout << "Input anything to return: " << endl;
	string OP;
	cin >> OP;
	return;
}

void Get_Stone_FreeEXP(LL lv)
{
	system("cls");
	cout << endl;
	cout << "           *   *   *****  *   *   *" << endl;
	cout << "           *   *     *    **  *   *" << endl;
	cout << "           * * *     *    * * *   *" << endl;
	cout << "           * * *     *    *  **" << endl;
	cout << "            * *    *****  *   *   *" << endl; 
	cout << endl << endl << endl;
	LL YW, FR;
	if (lv == 100) YW = 300, FR = 5000;
	else if (lv == 90) YW = 200, FR = 3250;
	else if (lv == 70) YW = 150, FR = 2500;
	else YW = 100, FR = 1500;
	cout.width(15); cout << " ";
	cout << "获得愿望值  " << YW << endl;
	cout.width(15); cout << " ";
	cout << "获得经验值  " << FR << endl;
	stone += YW; free_exp += FR; 
	cout << "-------------------------------------------------";
	cout << "Input anything to return: " << endl;
	string OP;
	cin >> OP;
	return;
}

void Battle_Mode(LL Level)
{
	LL eID = rand() % 21 + 1;
	if (eID == 20) --eID; 
	LL cID = Choose_Pokemon(Level, eID), mID;
	LL win = 0;
	if (cID == -1) Game_Menu();
	else
	{
		PM_Battle myPm(pm[cID].get_ID(), pm[cID].get_LV(), pm[cID].get_EXP());
		mID = myPm.get_ID();
		vector<LL> my_skill = pm_data[mID].get_skill();
		PM_Battle enPm(eID, Level, 0);
		Before_Battle(myPm, enPm);
		string EnemyComeOut = pm_data[eID].get_name() + "出现了！"; 
		Battle_Output(myPm, enPm, EnemyComeOut);
		string my_name = pm_data[mID].get_name();
		string en_name = pm_data[eID].get_name();
		while (1)
		{
			Battle_Output(myPm, enPm, my_name + "要做什么？"); 
			print_SKILL(myPm); 
			string OP; cin >> OP;
			LL used_skill = 0, used_id = 0;
			if (OP.compare("2") == 0) { used_skill = my_skill[1]; used_id = 2; }
			else if (OP.compare("3") == 0) { used_skill = my_skill[2]; used_id = 3; }
			else if (OP.compare("4") == 0) { used_skill = my_skill[3]; used_id = 4; }
			else { used_skill = my_skill[0]; used_id = 1; }
			
			vector<LL> en_can_use, en_skill = pm_data[eID].get_skill();
			for (LL i = 0; i <= 3; ++i)
			{
				if (enPm.pp[i + 1] > 0) en_can_use.push_back(i);
			}
			LL choose_en = rand() % en_can_use.size();
			LL en_skill_id = en_can_use[choose_en] + 1; LL en_used_skill = en_skill[en_skill_id - 1];
			
			Use_Skill(myPm, enPm, used_skill, en_used_skill);
			
			LL check_res = check_not_finish(myPm, enPm);
			if (check_res == 1)
			{
				Battle_Output(myPm, enPm, "击败了" + en_name + "！");
				win = 1;
				break;
			}
			else if (check_res == -1)
			{
				Battle_Output(myPm, enPm, "被" + en_name + "击败了...");
				win = 0;
				break;
			}
		}
		if (!win) return;
		Win_Get_EXP(Level, mID);
		Get_Stone_FreeEXP(Level);
	}
}

inline void Battle_Field()
{
	system("cls");
	cout << "愿望值：" << stone << endl;
	cout << "经验值：" << free_exp << endl << endl; 
	cout << "-------------------------" << endl;
	MenuGroup("1.金与银之歌 Lv.50", "愿望值100+经验值1500");
	MenuGroup("2.空与时之叹 Lv.70", "愿望值150+经验值2500");
	MenuGroup("3.黑与白之诗 Lv.90", "愿望值200+经验值3250");
	MenuGroup("4.日与月之梦 Lv.100", "愿望值300+经验值5000"); 
	cout << "输入挑战编号以进入对应挑战。" << endl;
	cout << "输入其他内容以退出挑战页面。" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "Option: ";
	string OP; cin >> OP; 
	if (OP.compare("1") == 0) Battle_Mode(50);
	else if (OP.compare("2") == 0) Battle_Mode(70);
	else if (OP.compare("3") == 0) Battle_Mode(90);
	else if (OP.compare("4") == 0) Battle_Mode(100);
	Game_Menu();
}

LL Get_Pokemon(LL pid)
{
	LL ret = 0;
	system("cls");
	cout << endl << endl;
	cout.width(25); cout << " "; cout << "获得新宝可梦！" << endl << endl; 
	cout.width(25); cout << " ";
	cout << pm_data[pid].get_name() << endl << endl;
	LL pos = -1;
	for (LL i = 0; i < pm_ammount; ++i)
	{
		if (pm[i].get_ID() == pid)
		{
			pos = i; break;
		}
	}
	if (pos >= 0)
	{
		ret = 1;
		cout.width(25); cout << " "; cout << "获得重复宝可梦，转化成多余经验值" << endl;
		cout.width(25); cout << " "; cout << "EXP +" << value_exp[pm_data[pid].get_exp_type()] << endl;
		free_exp += value_exp[pm_data[pid].get_exp_type()];
	}
	else 
	{
		++pm_ammount;
		POKEMON tmp(pid, 50ll, 0ll);
		pm.push_back(tmp); 
	}
	cout << "------------------------------------------" << endl;
	cout << "Input anything to continue:";
	string OP; cin >> OP;
	return ret;
}

void Get_EXP(LL E)
{
	system("cls");
	cout << endl << endl;
	cout.width(25); cout << " "; cout << "获得经验值！" << endl << endl; 
	cout.width(25); cout << " "; cout << E << endl << endl;
	cout.width(25); cout << " ";
	cout << "经验值：" << free_exp << " -> ";
	free_exp += E;
	cout << free_exp << endl << endl;
	cout << "------------------------------------------" << endl;
	cout << "Input anything to continue:";
	string OP; cin >> OP;
}

void Pokemon_Detail(LL pos)
{
	system("cls");
	pm[pos].show();
	cout << "-------------------------" << endl;
	cout << "Input anything to return to the GameMenu." << endl;
	string OP; cin >> OP;
	Game_Menu();
}

LL Choose_MyPokemon()
{
	cout << "-------------------------" << endl;
	for (LL i = 0; i < pm_ammount; ++i)
	{
		MenuGroup(to_string(i + 1) + "." + pm_data[pm[i].get_ID()].get_name(), "Lv." + to_string(pm[i].get_LV()));
	}
	cout << "Input number before the Pokemon." << endl;
	string OP; cin >> OP;
	LL len = OP.length(), all_degit = 1, op;
	for (LL i = 0; i < len; ++i)
	{
		if (OP[i] < '0' || OP[i] > '9')
		{
			all_degit = 0;
			break;
		}
	}
	if (len > 2) return -1;
	op = string_int(OP);
	if (0 < op && op <= pm_ammount) return op - 1;
	else return -1;
}

void Pokemon_Upgrade()
{
	system("cls");
	cout << "愿望值：" << stone << endl;
	cout << "经验值：" << free_exp << endl << endl; 
	LL pos = Choose_MyPokemon();
	cout << "使用多少经验值？" << endl; 
	string OP; cin >> OP;
	LL len = OP.length(), all_degit = 1, op;
	for (LL i = 0; i < len; ++i)
	{
		if (OP[i] < '0' || OP[i] > '9')
		{
			all_degit = 0;
			break;
		}
	}
	if (all_degit == 0)
	{
		cout << "输入不合法。" << endl; 
		cout << "------------------------------------------" << endl;
		cout << "Input anything to return:";
		string OP; cin >> OP;
		Pokemon_Upgrade(); 
	}
	if (len > 18)
	{
		cout << "数值太大了！" << endl; 
		cout << "------------------------------------------" << endl;
		cout << "Input anything to return:";
		string OP; cin >> OP;
		Pokemon_Upgrade();  
	}
	op = string_int(OP);
	if (op > free_exp)
	{
		cout << "数值太大了！" << endl; 
		cout << "------------------------------------------" << endl;
		cout << "Input anything to return:";
		string OP; cin >> OP;
	}
	else
	{
		pm[pos].set_exp(op);
		free_exp -= op;
		cout << "升级成功！" << endl; 
		cout << "------------------------------------------" << endl;
		cout << "Input anything to return:";
		string OP; cin >> OP;
	}
	Pokemon_Upgrade(); 
}

void My_Pokemon()
{
	system("cls");
	cout << "我的宝可梦：" << endl;
	LL ID = Choose_MyPokemon();
	if (ID >= 0) Pokemon_Detail(ID);
	else Game_Menu();
}

void show_result(vector<pair<LL, LL> > res)
{
	system("cls");
	LL wish_exp = 0;
	cout.width(25); cout << "祈愿结果：" << endl; 
	for (LL i = 0; i < res.size(); ++i)
	{
		LL x = res[i].first, y = res[i].second;
		if (x <= 30)
		{
			cout.width(20);
			cout << pm_data[x].get_name();
			if (y == 1) cout << "  ---已转化为经验值";
		}
		else if (x > 30)
		{
			if (x == 31) wish_exp += 50000;
			else if (x == 32) wish_exp += 20000;
			else if (x == 33) wish_exp += 10000;
			continue;
		}
		cout << endl;
		LL c1 = clock();
		while (1)
		{
			if (clock() - c1 > 100) break;
		}
	}
	cout.width(20); cout << "经验值";
	cout << "  " << wish_exp << endl; 
	cout << "-------------------------" << endl;
	cout << "请按任意键并回车以返回祈愿界面。" << endl;
	string OP; cin >> OP;
	return; 
}

void Wish(LL Wt)
{
	vector<pair<LL, LL> > res;
	for (LL i = 1; i <= Wt; ++i)
	{
		system("cls");
		LL c1 = clock();
		cout.width(8); cout << " "; cout << "正在进行第" << i << "次祈愿" << endl << endl;
		LL A = rand() % 10000 + 1;
		cout.width(13); cout << " ";
		for (LL i = 1; i <= 29; ++i)
		{
			c1 = clock();
			cout << "."; 
			while (1) { if (clock() - c1 > 30) break; }
		}
		cout << "!";
		c1 = clock();
		while (1) { if (clock() - c1 > 500) break; }
		LL yes;
		if (1 <= A && A <= 280) { yes = Get_Pokemon(6); res.push_back(make_pair(6, yes)); }
		else if (281 <= A && A <= 370) { yes = Get_Pokemon(15); res.push_back(make_pair(15, yes)); }
		else if (371 <= A && A <= 410) { yes = Get_Pokemon(1); res.push_back(make_pair(1, yes)); }
		else if (311 <= A && A <= 450) { yes = Get_Pokemon(3); res.push_back(make_pair(3, yes)); }
		else if (451 <= A && A <= 490) { yes = Get_Pokemon(4); res.push_back(make_pair(4, yes)); }
		else if (491 <= A && A <= 530) { yes = Get_Pokemon(5); res.push_back(make_pair(5, yes)); }
		else if (531 <= A && A <= 570) { yes = Get_Pokemon(7); res.push_back(make_pair(7, yes)); }
		else if (571 <= A && A <= 610) { yes = Get_Pokemon(8); res.push_back(make_pair(8, yes)); }
		else if (611 <= A && A <= 650) { yes = Get_Pokemon(9); res.push_back(make_pair(9, yes)); }
		else if (651 <= A && A <= 690) { yes = Get_Pokemon(10); res.push_back(make_pair(10, yes)); }
		else if (691 <= A && A <= 730) { yes = Get_Pokemon(11); res.push_back(make_pair(11, yes)); }
		else if (731 <= A && A <= 770) { yes = Get_Pokemon(12); res.push_back(make_pair(12, yes)); }
		else if (771 <= A && A <= 810) { yes = Get_Pokemon(13); res.push_back(make_pair(13, yes)); }
		else if (811 <= A && A <= 850) { yes = Get_Pokemon(14); res.push_back(make_pair(14, yes)); }
		else if (851 <= A && A <= 890) { yes = Get_Pokemon(16); res.push_back(make_pair(16, yes)); }
		else if (891 <= A && A <= 930) { yes = Get_Pokemon(18); res.push_back(make_pair(18, yes)); }
		else if (931 <= A && A <= 970) { yes = Get_Pokemon(20); res.push_back(make_pair(20, yes)); }
		else if (971 <= A && A <= 980) { yes = Get_Pokemon(17); res.push_back(make_pair(17, yes)); }
		else if (981 <= A && A <= 990) { yes = Get_Pokemon(19); res.push_back(make_pair(19, yes)); }
		else if (991 <= A && A <= 1000) { yes = Get_Pokemon(22); res.push_back(make_pair(22, yes)); }
		else if (1001 <= A && A <= 3000) { Get_EXP(50000); res.push_back(make_pair(31, 0)); }
		else if (3001 <= A && A <= 6000) { Get_EXP(20000); res.push_back(make_pair(32, 0)); }
		else { Get_EXP(10000); res.push_back(make_pair(33, 0)); }
	}
	show_result(res);
}

void Pokemon_Wish()
{
	cout << "愿望值：" << stone << endl;
	cout << "经验值：" << free_exp << endl << endl; 
	cout.width(12); cout << " ";cout << "宝可梦祈愿" << endl;
	cout << endl;
	cout << "       *   *   *****   ****   *   *" << endl;
	cout << "       *   *     *    *       *   *" << endl;
	cout << "       * * *     *    *****   *****" << endl;
	cout << "       * * *     *        *   *   *" << endl;
	cout << "        * *    *****  ****    *   *" << endl; 
	cout << endl << endl << endl;
	cout << "-------------------------" << endl;
	MenuGroup("1. 1次祈愿", "愿望值- 300");
	MenuGroup("2. 5次祈愿", "愿望值-1400");
	MenuGroup("3.10次祈愿", "愿望值-2700"); 
	cout << "输入祈愿项目前的编号以执行祈愿。" << endl;
	cout << "输入其他则退出祈愿界面。" << endl;
	LL c1;
	string OP; cin >> OP;
	if (OP.compare("1") == 0)
	{
		if (stone < 300)
		{
			cout << "愿望值不足！" << endl;
			cout << "------------------------------------------" << endl;
			cout << "Input anything to return:";
			string OP; cin >> OP;
		}
		else
		{
			Wish(1);
			stone -= 300;
		}
		Pokemon_Wish();
	}
	else if (OP.compare("2") == 0)
	{
		if (stone < 1400)
		{
			cout << "愿望值不足！" << endl;
			cout << "------------------------------------------" << endl;
			cout << "Input anything to return:";
			string OP; cin >> OP;
		}
		else
		{
			Wish(5);
			stone -= 1400;
		}
		Pokemon_Wish();
	}
	else if (OP.compare("3") == 0)
	{
		if (stone < 2700)
		{
			cout << "愿望值不足！" << endl;
			cout << "------------------------------------------" << endl;
			cout << "Input anything to return:";
			string OP; cin >> OP;
		}
		else
		{
			Wish(10);
			stone -= 2700;
		}
		Pokemon_Wish(); 
	}
	else Game_Menu(); 
}

//void Save_Data1(LL Y, LL M1, LL D, LL H, LL M2, LL S)
//{
//	ofstream out("Save1.txt");
//	out << pm_ammount << " " << Y << " " << M1 << " " << D << " " << H << " " << M2 << " " << S << endl;
//	out << stone << " " << free_exp << endl;
//	for (LL i = 0; i < pm_ammount; ++i)
//	{
//		out << pm[i].get_ID() << " " << pm[i].get_LV() << " " << pm[i].get_EXP() << endl;
//	}
//	out.close();
//}

//void Save_Data2(LL Y, LL M1, LL D, LL H, LL M2, LL S)
//{
//	ofstream out("Save2.txt");
//	out << pm_ammount << " " << Y << " " << M1 << " " << D << " " << H << " " << M2 << " " << S << endl;
//	out << stone << " " << free_exp << endl;
//	for (LL i = 0; i < pm_ammount; ++i)
//	{
//		out << pm[i].get_ID() << " " << pm[i].get_LV() << " " << pm[i].get_EXP() << endl;
//	}
//	out.close();
//}

//void Save_Data3(LL Y, LL M1, LL D, LL H, LL M2, LL S)
//{
//	ofstream out("Save3.txt");
//	out << pm_ammount << " " << Y << " " << M1 << " " << D << " " << H << " " << M2 << " " << S << endl;
//	out << stone << " " << free_exp << endl;
//	for (LL i = 0; i < pm_ammount; ++i)
//	{
//		out << pm[i].get_ID() << " " << pm[i].get_LV() << " " << pm[i].get_EXP() << endl;
//	}
//	out.close();
//}

void Save_Data()
{
	system("cls");
	cout << "Saving Data..." << endl;
	time_t t = time(NULL); tm *lt;
	lt = localtime(&t);
	LL hour = lt->tm_hour, minute = lt->tm_min, second = lt->tm_sec;
	LL year = lt->tm_year + 1900, month = lt->tm_mon, day = lt->tm_mday; 
	if (SaveID == 1) Saving1.Save_Data(year, month, day, hour, minute, second);
	else if (SaveID == 2) Saving2.Save_Data(year, month, day, hour, minute, second);
	else Saving3.Save_Data(year, month, day, hour, minute, second);
	cout << "-------------------------" << endl;
	cout << "输入任意键并回车返回游戏菜单。" << endl;
	string OP; cin >> OP;
	return;
}

void Game_Menu()
{
	system("cls");
	freopen("CON", "r", stdin);
	cout << "愿望值：" << stone << endl;
	cout << "经验值：" << free_exp << endl << endl; 
	cout << "-------------------------" << endl;
	MenuGroup("1.出征！", "Battle Field");
	MenuGroup("2.我的宝可梦", "My Pokemon");
	MenuGroup("3.宝可梦祈愿", "Pokemon Wish");
	MenuGroup("4.宝可梦提升", "Pokemon Upgrade"); 
	MenuGroup("5.保存记录", "Save"); 
	cout << "输入选项编号以进入对应页面。" << endl;
	cout << "输入其他内容可以退出当前界面。" << endl; 
	cout << "-----------------------------------------" << endl;
	cout << "Option: ";
	string OP; cin >> OP; 
	if (OP.compare("1") == 0) { Battle_Field(); Game_Menu(); }
	else if (OP.compare("2") == 0) { My_Pokemon(); Game_Menu(); }
	else if (OP.compare("3") == 0) { Pokemon_Wish(); Game_Menu(); }
	else if (OP.compare("4") == 0) { Pokemon_Upgrade(); Game_Menu(); }
	else if (OP.compare("5") == 0) { Save_Data(); Game_Menu(); }
	else if (OP.compare("XINDALAOTONGZHISHIJIE") == 0) { Get_Pokemon(20); Game_Menu(); }
	else if (OP.compare("PresentPikachuForZZT") == 0) { Get_Pokemon(22); Game_Menu(); } 
	else
	{
		cout << "确认返回吗？请确保记录已经保存。" << endl;
		cout << "如确认，请输入Y。" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "Option: ";
		string NY; cin >> NY;
		if (NY.compare("Y") == 0) return;
		else Game_Menu();
	}
}

//void Load_File1()
//{
//	SaveID = 1;
//	ifstream in("Save1.txt");
//	in >> pm_ammount;
//	if (pm_ammount == -1)
//	{
//		POKEMON tmp(21, 50, 0);
//		pm.push_back(tmp); pm_ammount = 1;
//	}
//	else
//	{
//		in >> Year >> Month >> Day >> Hour >> Minute >> Second;
//		in >> stone >> free_exp;
//		pm.clear();
//		for (LL i = 1; i <= pm_ammount; ++i)
//		{
//			LL pm_id, pm_lv, pm_exp;
//			in >> pm_id >> pm_lv >> pm_exp;
//			POKEMON tmp(pm_id, pm_lv, pm_exp);
//			pm.push_back(tmp);
//		}
//	}
//	sort(pm.begin(), pm.end());
//	in.close();
//	Game_Menu(); 
//}

//void Load_File2()
//{
//	SaveID = 2;
//	ifstream in("Save2.txt");
//	in >> pm_ammount;
//	if (pm_ammount == -1)
//	{
//		POKEMON tmp(21, 50, 0);
//		pm.push_back(tmp); pm_ammount = 1;
//	}
//	else
//	{
//		in >> Year >> Month >> Day >> Hour >> Minute >> Second;
//		in >> stone >> free_exp;
//		pm.clear();
//		for (LL i = 1; i <= pm_ammount; ++i)
//		{
//			LL pm_id, pm_lv, pm_exp;
//			in >> pm_id >> pm_lv >> pm_exp;
//			POKEMON tmp(pm_id, pm_lv, pm_exp);
//			pm.push_back(tmp);
//		}
//		sort(pm.begin(), pm.end());
//	}
//	in.close();
//	Game_Menu();
//}

//void Load_File3()
//{
//	SaveID = 3;
//	ifstream in("Save3.txt");
//	in >> pm_ammount;
//	if (pm_ammount == -1)
//	{
//		POKEMON tmp(21, 50, 0);
//		pm.push_back(tmp); pm_ammount = 1;
//	}
//	else
//	{
//		in >> Year >> Month >> Day >> Hour >> Minute >> Second;
//		in >> stone >> free_exp;
//		pm.clear();
//		for (LL i = 1; i <= pm_ammount; ++i)
//		{
//			LL pm_id, pm_lv, pm_exp;
//			in >> pm_id >> pm_lv >> pm_exp;
//			POKEMON tmp(pm_id, pm_lv, pm_exp);
//			pm.push_back(tmp);
//		}
//		sort(pm.begin(), pm.end());
//	}
//	in.close();
//	Game_Menu();
//}

//void Delete_File1()
//{
//	ofstream out("Save1.txt");
//	out << "-1";
//	out.close();
//}
//
//void Delete_File2()
//{
//	ofstream out("Save2.txt");
//	out << "-1";
//	out.close();
//}
//
//void Delete_File3()
//{
//	ofstream out("Save3.txt");
//	out << "-1";
//	out.close();
//}

void output_time(LL Y, LL Mon, LL D, LL H, LL M, LL S)
{
	cout << Y << "/" << Mon << "/" << D << " " << H << ":";
	if (M < 10) cout << "0";
	cout << M << ":";
	if (S < 10) cout << "0";
	cout << S;
}

LL ok1 = 0, ok2 = 0, ok3 = 0;
LL x1, Y1, m1, d1, h1, mi1, s1; 
LL x2, y2, m2, d2, h2, mi2, s2; 
LL x3, y3, m3, d3, h3, mi3, s3; 

void take_save1()
{
	cout << "Save 1: " << endl;
	ifstream in("Save1.txt"); 
	in >> x1;
	if (x1 == -1) cout << "No data\n";
	else 
	{
		in >> Y1 >> m1 >> d1 >> h1 >> mi1 >> s1;
		output_time(Y1, m1, d1, h1, mi1, s1);
		cout << ", " << x1 << " pokemon";
		if (x1 > 1) cout << "s";
		cout << endl;
		ok1 = 1;
	}
	cout << endl;
	in.close();
}

void take_save2()
{
	cout << "Save 2: " << endl;
	ifstream in2("Save2.txt");
	in2 >> x2;
	if (x2 == -1) cout << "No data" << endl;
	else
	{
		in2 >> y2 >> m2 >> d2 >> h2 >> mi2 >> s2;
		output_time(y2, m2, d2, h2, mi2, s2);
		cout << ", " << x1 << " pokemon";
		if (x2 > 1) cout << "s";
		cout << endl;
		ok2 = 1;
	}
	cout << endl;
	in2.close();
}

void take_save3()
{
	cout << "Save 3: " << endl;
	ifstream in3("Save3.txt");
	in3 >> x3;
	if (x3 == -1) printf("No data\n");
	else
	{
		in3 >> y3 >> m3 >> d3 >> h3 >> mi3 >> s3;
		output_time(y3, m3, d3, h3, mi3, s3);
		cout << ", " << x1 << " pokemon";
		if (x3 > 1) cout << "s";
		cout << endl;
		ok3 = 1;
	}
	cout << endl;
	in3.close();
}

void Select_Save()
{
	system("cls");
	take_save1();
	take_save2();
	take_save3();
	cout << "------------------------------------" << endl;
	cout << "input 1 to choose save 1" << endl;
	cout << "input 2 to choose save 2" << endl;
	cout << "input 3 to choose save 3" << endl;
	cout << "input M to delete savings" << endl;
	cout << "input others to return to the title" << endl;
	string OP; cin >> OP;
	if (OP.compare("1") == 0) Saving1.Load_File();
	else if (OP.compare("2") == 0) Saving2.Load_File();
	else if (OP.compare("3") == 0) Saving3.Load_File();
	else if (OP.compare("M") == 0)
	{
		system("cls");
		cout << "Save 1: ";
		if (!ok1) cout << "No data";
		else output_time(Y1, m1, d1, h1, mi1, s1);
		cout << "\n\nSave 2: ";
		if (!ok2) cout << "No data";
		else output_time(y2, m2, d2, h2, mi2, s2);
		cout << "\n\nSave 3: ";
		if (!ok3) cout << "No data";
		else output_time(y3, m3, d3, h3, mi3, s3);
		cout << "\n\n";
		cout << "input 1 to delete save 1" << endl;
		cout << "input 2 to delete save 2" << endl;
		cout << "input 3 to delete save 3" << endl;
		cout << "input others to return." << endl;
		cin >> OP;
		if (OP.compare("1") == 0) 
		{
			Saving1.Delete_File(); //Select_Save();
		}
		else if (OP.compare("2") == 0)
		{
			Saving2.Delete_File(); //Select_Save();
		}
		else if (OP.compare("3") == 0) 
		{
			Saving3.Delete_File(); //Select_Save();
		}
		else Select_Save();
	}
	else Title();
}

void Title()
{
	system("cls");
	freopen("CON", "r", stdin);
	cout << "****    ***   *  **  *****  *   *   ***   *   *" << endl;
	cout << "*   *  *   *  * *    *      ** **  *   *  **  *" << endl;
	cout << "****   *   *  **     ****   * * *  *   *  * * *" << endl;
	cout << "*      *   *  * *    *      *   *  *   *  *  **" << endl;
	cout << "*       ***   *  **  *****  *   *   ***   *   *" << endl;
	cout << endl << endl;
	cout << "              Input 1 to start" << endl;
	cout << "            Input others to close" << endl;
	cout << "---------------------------------------------" << endl;
	cout << "Option:" << endl ;
	string OP;
	cin >> OP;
	cout << endl;
	if (OP.compare("1") == 0)
	{
		Select_Save();
		Title();
	} 
	else return;
}

int main()
{
	srand(time(0));
	Init();
	system("cls");
	Title();
	return 0;
}
