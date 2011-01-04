
#include "cspec.h"

static int nbefore = 0;
static int nbefore_each = 0;
static int nafter = 0;
static int nafter_each = 0;

static int foo()  { return 4; }
static int bar(int n) { return n * n; }



 void block_0_callback() {
    ++nbefore;
 
}
  
 void block_1_callback() {
    ++nafter;
 
}
  
  void block_2_callback() {

    expect((match_equal(nbefore,  1)));
;
 
}
  
  void block_3_callback() {

    expect((match_equal(nbefore,  1)));
;
 
}


  void block_4_callback() {

    expect((match_equal(nafter,  1)));
;
 
}
  
  void block_5_callback() {

    expect((match_equal(nafter,  1)));
;
 
}


 void block_6_callback() {
    ++nbefore_each;
 
}
  
  void block_7_callback() {

    expect((match_equal(nbefore_each,  1)));
;
 
}
  
  void block_8_callback() {

    expect((match_equal(nbefore_each,  2)));
;
 
}


 void block_9_callback() {
    ++nafter_each;
 
}
  
  void block_10_callback() {

    expect((match_equal(nafter_each,  0)));
;
 
}
  
  void block_11_callback() {

    expect((match_equal(nafter_each,  1)));
;
 
}


  void block_12_callback() {

    int foo = 1;
    expect((match_equal(foo,  1)));

 
}
  
  void block_13_callback() {

    int foo = 1;
    expect((match_equal(foo,  1)));
;
 
}
  
  void block_14_callback() {

    char *foo_bar = "test";
    expect((match_equal(foo_bar,  "test")));
;
 
}
  
  void block_15_callback() {

    struct { int x, y; } point = { 0, 1 };
    expect((match_equal(point.x,  0)));
;
    expect((match_equal(point.y,  1)));
;
 
}
  
  void block_16_callback() {

    Suite *foo = Suite_new("Something");
    expect((match_equal(foo->description,  "Something")));
;
 
}
  
  void block_17_callback() {

    expect((match_equal(foo(),  4)));
;
    expect((match_equal(bar(2),  4)));
;
 
}
  
  void block_18_callback() {

    char *foo = "test";
    expect((match_equal(foo[0],  't')));
;
    expect((match_equal(foo[1],  'e')));
;
 
}
  
  void block_19_callback() {

    Suite *foo = Suite_new("Something");
    expect((match_equal(foo->description[0],  'S')));
;
 
}
  
  void block_20_callback() {

    expect(!(match_equal(foo(),  5)));
;
 
}


  void block_21_callback() {

    char *a = strdup("foo");
    char *b = strdup("foo");
    expect(!(match_equal(a,  b)));
;
    a = b;
    expect((match_equal(a,  b)));
;
 
}
  
  void block_22_callback() {

    expect((match_be(NULL,  NULL)));
;
 
}
  
  void block_23_callback() {

    expect((match_point_to(NULL,  NULL)));
;
 
}
  
  void block_24_callback() {

    expect((match_include(strdup("foobar"),  strdup("foo"))));
;
    expect(!(match_include(strdup("foobar"),  strdup("baz"))));
;
 
}
  
  void block_25_callback() {

    expect((match_start_with("foobar",  "foo")));
;
    expect(!(match_start_with("barfoo",  "foo")));
;
 
}
int main() {

Suite *suite_0 = Suite_new("CSpec before");

 
Block *block_0 = Block_new(blockTypeBefore, NULL, &block_0_callback);

Suite_push_block(suite_0, block_0);

Block *block_1 = Block_new(blockTypeAfter, NULL, &block_1_callback);

Suite_push_block(suite_0, block_1);

Block *block_2 = Block_new(blockTypeSpec, "should be called before each suite", &block_2_callback);

Suite_push_block(suite_0, block_2);

Block *block_3 = Block_new(blockTypeSpec, "should not be called before each spec", &block_3_callback);

Suite_push_block(suite_0, block_3);

Suite *suite_1 = Suite_new("CSpec after");

Suite_push_suite(suite_0, suite_1);

Block *block_4 = Block_new(blockTypeSpec, "should be called after each suite", &block_4_callback);

Suite_push_block(suite_1, block_4);

Block *block_5 = Block_new(blockTypeSpec, "should not be called after each spec", &block_5_callback);

Suite_push_block(suite_1, block_5);

Suite *suite_2 = Suite_new("CSpec before_each");

Suite_push_suite(suite_1, suite_2);

Block *block_6 = Block_new(blockTypeBeforeEach, NULL, &block_6_callback);

Suite_push_block(suite_2, block_6);

Block *block_7 = Block_new(blockTypeSpec, "should be called before each spec", &block_7_callback);

Suite_push_block(suite_2, block_7);

Block *block_8 = Block_new(blockTypeSpec, "should be called before each spec", &block_8_callback);

Suite_push_block(suite_2, block_8);

Suite *suite_3 = Suite_new("CSpec after_each");

Suite_push_suite(suite_2, suite_3);

Block *block_9 = Block_new(blockTypeAfterEach, NULL, &block_9_callback);

Suite_push_block(suite_3, block_9);

Block *block_10 = Block_new(blockTypeSpec, "should be called after each spec", &block_10_callback);

Suite_push_block(suite_3, block_10);

Block *block_11 = Block_new(blockTypeSpec, "should be called after each spec", &block_11_callback);

Suite_push_block(suite_3, block_11);

Suite *suite_4 = Suite_new("CSpec assertions");

Suite_push_suite(suite_3, suite_4);

Block *block_12 = Block_new(blockTypeSpec, "should work without semicolons", &block_12_callback);

Suite_push_block(suite_4, block_12);

Block *block_13 = Block_new(blockTypeSpec, "should work with ids", &block_13_callback);

Suite_push_block(suite_4, block_13);

Block *block_14 = Block_new(blockTypeSpec, "should work with underscored ids", &block_14_callback);

Suite_push_block(suite_4, block_14);

Block *block_15 = Block_new(blockTypeSpec, "should work with structures", &block_15_callback);

Suite_push_block(suite_4, block_15);

Block *block_16 = Block_new(blockTypeSpec, "should work with pointers to structures", &block_16_callback);

Suite_push_block(suite_4, block_16);

Block *block_17 = Block_new(blockTypeSpec, "should work with function calls", &block_17_callback);

Suite_push_block(suite_4, block_17);

Block *block_18 = Block_new(blockTypeSpec, "should work with subscripts", &block_18_callback);

Suite_push_block(suite_4, block_18);

Block *block_19 = Block_new(blockTypeSpec, "should work with pointers to structures using subscripts", &block_19_callback);

Suite_push_block(suite_4, block_19);

Block *block_20 = Block_new(blockTypeSpec, "should be negatable", &block_20_callback);

Suite_push_block(suite_4, block_20);

Suite *suite_5 = Suite_new("CSpec matchers");

Suite_push_suite(suite_4, suite_5);

Block *block_21 = Block_new(blockTypeSpec, "equal should assert that two pointers are the same", &block_21_callback);

Suite_push_block(suite_5, block_21);

Block *block_22 = Block_new(blockTypeSpec, "be should alias equal", &block_22_callback);

Suite_push_block(suite_5, block_22);

Block *block_23 = Block_new(blockTypeSpec, "point_to should alias equal", &block_23_callback);

Suite_push_block(suite_5, block_23);

Block *block_24 = Block_new(blockTypeSpec, "include should assert that a substring is present", &block_24_callback);

Suite_push_block(suite_5, block_24);

Block *block_25 = Block_new(blockTypeSpec, "start_with should assert that a substring is at the beginning", &block_25_callback);

Suite_push_block(suite_5, block_25);

Suite_run(suite_0);
CSpec_stats();
return CSpec.failures;
}


