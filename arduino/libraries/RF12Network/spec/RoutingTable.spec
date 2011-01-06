#include "cspec.h"
#include "defines.h"
#include <RoutingTable.h>

RoutingTable<255> table;

describe "RoutingTable"
  before
    table.AddNode(3, table.GetRoot());
    table.AddNode(4, table.GetRoot());
    table.AddNode(55, table.GetRoot());
    table.AddNode(7, 4);
    table.AddNode(6, 7);
  end
  
  it "nodes should be findable"
    (table.Find(88)) should equal 0;
    table.Find(6) should equal 6;
    table.Find(55) should equal 55;
  end
  
  it "nodes should be removeable"
    table.Find(6) should equal 6;
    table.Remove(6)
    table.Find(6) should equal 0;
  end
end
