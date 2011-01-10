#ifndef __TREE_H_
#define __TREE_H_

template <uint8_t size>
class RoutingTable
{
  typedef struct node_t
  {
    node_t() : parent(0) {}; 
    node_id parent; 
  } node_t;

  node_id root;
  node_t nodes[size];

public:
  RoutingTable() {
    SetRoot(0xFF);
  };

  inline void SetRoot(node_id id) {
    root = id;
    nodes[root].parent = root;
  }

  inline node_id GetRoot() {
    return root;
  }
  
  node_id Find(node_id val) {
    return nodes[val].parent != 0 ? val : 0;
  };
  
  // finds the the item and returns the node next to root
  // example:
  /*      
          ROOT         
          / \      
         /   \     
        G     W    
       / \         
      /   \        
     D     M       
    / \     \      
   B   F     P  
   
   if you search for node F it will return value of node G 
   
   RoutingTable<127> t;
   t.find_next_child(F) == G;
 */
  node_id FindNextHop(node_id val) {
    node_id found = Find(val);
    if(found == 0) return 0;

    node_t node = nodes[found];
    
    while(node.parent != root) {
      if(node.parent == 0) return 0;
      found = node.parent;
      node = nodes[node.parent];
    }
    
    return found;
  };
  
  void AddNode(node_id val, node_id after) 
  {// TODO: was machen wenn er die node id von sich selber gibt?
    if(nodes[after].parent == 0) return; // wtf?
    LOGN2(6, "Added to table [node, parent]", val, after);

    nodes[val].parent = after;
  };
  
  void RemoveNode(node_id val) {
    node_t n = nodes[val];

    // TODO: find a method to do this in less than O(n)
    for(uint8_t i = 0; i < size; ++i) {
      if(nodes[i].parent == val) 
        nodes[i].parent = 0; 
    }

    LOGN(6, "Removed node", val);

    nodes[val].parent = 0;
  };
};

#endif