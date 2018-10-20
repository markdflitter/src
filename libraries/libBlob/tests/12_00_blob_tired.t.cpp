#include <gtest/gtest.h>
#include "blob.h"
#include "blobImpl.h"

TEST (test_12_00_blob_tired_t, gets_tired_when_hunting_and_recovers)
{
	Blob attacker = CreateBlob ().lifespan (100000U).HP (100U).starvationLevel (10000U).position (make_pt (-100.0, -100.0)).speed (2.0).runningSpeed (20.0).endurance (2U);
	Blob target = CreateBlob ();
	
	EXPECT_FALSE (attacker.getImpl ()->_tired);

	std::shared_ptr<Action> a = attacker.createActionHunt (target);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	EXPECT_FALSE (attacker.getImpl ()->_tired);
	EXPECT_DOUBLE_EQ (m->_speed, 10.0);
	a->apply ();

	a = attacker.createActionHunt (target);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	m = std::dynamic_pointer_cast <Movement> (a);
	EXPECT_FALSE (attacker.getImpl ()->_tired);
	EXPECT_DOUBLE_EQ (m->_speed, 10.0);
	a->apply ();
	
	a = attacker.createActionHunt (target);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	m = std::dynamic_pointer_cast <Movement> (a);
	EXPECT_TRUE (attacker.getImpl ()->_tired);
	EXPECT_LT (m->_speed, 2.0);
	a->apply ();

	a = attacker.createActionHunt (target);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	m = std::dynamic_pointer_cast <Movement> (a);
	EXPECT_TRUE (attacker.getImpl ()->_tired);
	EXPECT_LT (m->_speed, 2.0);
	a->apply ();

	a = attacker.createActionHunt (target);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	m = std::dynamic_pointer_cast <Movement> (a);
	EXPECT_FALSE (attacker.getImpl ()->_tired);
	EXPECT_DOUBLE_EQ (m->_speed, 10.0);
	a->apply ();
}

TEST (test_12_00_blob_tired_t, gets_tired_when_fleeing_and_recovers)
{
	Blob runner = CreateBlob ().lifespan (10000U).HP (100U).starvationLevel (100000U).speed (20.0).runningSpeed (40.0).endurance (2U);
	Blob attacker = CreateBlob ();
	
	EXPECT_FALSE (runner.getImpl ()->_tired);

	std::shared_ptr<Action> a = runner.createActionFlee (attacker);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	EXPECT_FALSE (runner.getImpl ()->_tired);
	EXPECT_DOUBLE_EQ (m->_speed, 20.0);
	a->apply ();

	a = runner.createActionFlee (attacker);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	m = std::dynamic_pointer_cast <Movement> (a);
	EXPECT_FALSE (runner.getImpl ()->_tired);
	EXPECT_DOUBLE_EQ (m->_speed, 20.0);
	a->apply ();
	
	a = runner.createActionFlee (attacker);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	m = std::dynamic_pointer_cast <Movement> (a);
	EXPECT_TRUE (runner.getImpl ()->_tired);
	EXPECT_DOUBLE_EQ (m->_speed, 10.0);
	a->apply ();

	a = runner.createActionFlee (attacker);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	m = std::dynamic_pointer_cast <Movement> (a);
	EXPECT_TRUE (runner.getImpl ()->_tired);
	EXPECT_DOUBLE_EQ (m->_speed, 10.0);
	a->apply ();

	a = runner.createActionFlee (attacker);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	m = std::dynamic_pointer_cast <Movement> (a);
	EXPECT_FALSE (runner.getImpl ()->_tired);
	EXPECT_DOUBLE_EQ (m->_speed, 20.0);
	a->apply ();
}

