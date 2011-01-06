#include "cspec.h"
#include "defines.h"
#include <RoutingTable.h>

RoutingTable<255> table;



 void block_0_callback() {
    table.AddNode(3, table.GetRoot());
    table.AddNode(4, table.GetRoot());
    table.AddNode(55, table.GetRoot());
    table.AddNode(7, 4);
    table.AddNode(6, 7);
 
}
  
  void block_1_callback() {

    (table.Find(88)) should equal 0;
    table.expect((match_equal(Find(6),  6)));
;
    table.expect((match_equal(Find(55),  55)));
;
 
}
  
  void block_2_callback() {

    table.expect((match_equal(Find(6),  6)));
;
    table.Remove(6)
    table.expect((match_equal(Find(6),  0)));
;
 
}
int main() {

Suite *suite_0 = Suite_new("RoutingTable");

 
Block *block_0 = Block_new(blockTypeBefore, NULL, &block_0_callback);

Suite_push_block(suite_0, block_0);

Block *block_1 = Block_new(blockTypeSpec, "nodes should be findable", &block_1_callback);

Suite_push_block(suite_0, block_1);

Block *block_2 = Block_new(blockTypeSpec, "nodes should be removeable", &block_2_callback);

Suite_push_block(suite_0, block_2);

Suite_run(suite_0);
CSpec_stats();
return CSpec.failures;
}


