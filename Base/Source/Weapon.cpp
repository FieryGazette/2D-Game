#include "Weapon.h"
vector<Ammo*> Weapon::ammoList;

/* constructor/destructor */
Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}

/* core */
void Weapon::Init(WEAPON_TYPE type)
{
	ammo = 100;
	this->type = type;
	fireRate = 0.1;
	fireTimer = fireRate;
}

Ammo* Weapon::FetchAmmo()
{
	/* get ammo */
	for(int i = 0; i < ammoList.size(); ++i)
	{
		if( !ammoList[i]->getActive() )
		{
			ammoList[i]->setActive(true);
			return ammoList[i];
		}
	}

	/* create more ammo */
	ammoList.resize(ammoList.size() + 10);
	ammoList.back()->setActive(true);	//return last one
	return ammoList.back();
}

 void Weapon::InitAmmo(vector<Object*>& objectList)
 {
	 ammoList.resize(50);

	 for(int i = 0; i < ammoList.size(); ++i)
	 {
		 ammoList[i] = new Ammo;
		 ammoList[i]->Init(Ammo::PISTOL);
		 objectList.push_back(ammoList[i]);
	 }
 }


bool Weapon::Update(double dt, const Vector3& currentPos, Vector3& direction, bool fireWeapon)
{
	if( fireTimer < fireRate )
		fireTimer += dt;
	else
	{
		/* If fire */
		if( fireWeapon )
		{
			if( ammo > 0 )
			{
				Ammo* ammo_ptr = NULL;
				fireTimer = 0.0;

				ammo_ptr = FetchAmmo();
				ammo_ptr->Activate(currentPos, direction);
				--ammo;
				return true;
			}
		}
	}

	//zeo ammo
	return false;
}

void Weapon::UpdateAmmos(vector<Object*>& objectList)
{
	//loop thru all and update
	for(int i = 0; i < ammoList.size(); ++i)
	{
		if( ammoList[i]->getActive() )
			ammoList[i]->Update(objectList);
	}
}