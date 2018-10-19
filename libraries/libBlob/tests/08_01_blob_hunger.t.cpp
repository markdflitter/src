#include <gtest/gtest.h>
#include <blob.h>

TEST (test_08_01_blob_hunger_t, gets_hungrier)
{
	Blob b1 = CreateBlob ().HP (100U).lifespan (100U).starvationLevel (100U).speed (10.0);
	EXPECT_DOUBLE_EQ (b1.currentHunger (), 0.0);
	
	b1.getHungrier (22.0);
	EXPECT_DOUBLE_EQ (b1.currentHunger (), 22.0);
}


TEST (test_08_01_blob_hunger_t, gets_hungry_when_moving)
{
	Blob b1 = CreateBlob ().HP (100U).lifespan (100U).starvationLevel (100U).speed (10.0);
	EXPECT_DOUBLE_EQ (b1.currentHunger (), 0.0);
	
	b1.move (10.0, 0, "");
	EXPECT_DOUBLE_EQ (b1.currentHunger (), 10.0);
}

TEST (test_08_01_blob_hunger_t, gets_hungry_when_inflicting_damage)
{
	Blob attacker = CreateBlob ().HP (100U).damage (10U).lifespan (100U).starvationLevel (100U);
	Blob target = CreateBlob ().HP (100U).lifespan (100U).starvationLevel (100U);
	EXPECT_DOUBLE_EQ (attacker.currentHunger (), 0.0);
	
	attacker.inflictDamage (&target, "");
	EXPECT_DOUBLE_EQ (attacker.currentHunger (), 5.0);
}

TEST (test_08_01_blob_hunger_t, hunger_reduces_HP)
{
	Blob b1 = CreateBlob ().HP (100U).lifespan (100U).starvationLevel (100U);
	EXPECT_EQ (b1.currentHP (), 50U);

	b1.getHungrier (50.0);
	EXPECT_EQ (b1.currentHP (), 25U);
}

TEST (test_08_01_blob_hunger_t, hunger_starve_to_death)
{
	Blob b1 = CreateBlob ().HP (100U).lifespan (100U).starvationLevel (100U);
	EXPECT_EQ (b1.currentHP (), 50U);

	b1.getHungrier (100.0);
	EXPECT_TRUE (b1.isDead ());
}

