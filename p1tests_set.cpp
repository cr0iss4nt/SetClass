#include <gtest/gtest.h>
#include "bset.hpp"

TEST(SetTests, input) {
    Set set;
    set>>"{a, c, b,{e,d}}";
    EXPECT_EQ(set.intoString(),"{a, b, c, {d, e}}");
    set>>"{a, f}";
    EXPECT_EQ(set.intoString(),"{a, b, c, f, {d, e}}");
}

TEST(SetTests, union) {
    Set set,set2,set3,set4;
    set>>"{a, c, b,{e,d}}";
    set2>>"{f,g,h}";
    EXPECT_EQ((set+set2).intoString(),"{a, b, c, f, g, h, {d, e}}");
    set3>>"{{a,b,c},{f}}";
    EXPECT_EQ((set+set3).intoString(),"{a, b, c, {a, b, c}, {d, e}, {f}}");
    set+=set2;
    EXPECT_EQ(set.intoString(),"{a, b, c, f, g, h, {d, e}}");
    set4>>"{f,g,h,i}";
    EXPECT_EQ((set+set4).intoString(),"{a, b, c, f, g, h, i, {d, e}}");
}

TEST(SetTests, intersection) {
    Set set,set2,set3,set4;
    set>>"{a, c, b,{e,d}}";
    set2>>"{f,g,h}";
    EXPECT_EQ((set*set2).intoString(),"{}");
    set3>>"{{a,b,c},{d,e}}";
    EXPECT_EQ((set*set3).intoString(),"{{d, e}}");
    set*=set3;
    EXPECT_EQ(set.intoString(),"{{d, e}}");
    set4>>"{a,b,d,e}}";
    EXPECT_EQ((set*set4).intoString(),"{}");
}

TEST(SetTests, difference) {
    Set set,set2,set3,set4;
    set>>"{a, c, b,{e,d}}";
    set2>>"{a}";
    EXPECT_EQ((set-set2).intoString(),"{b, c, {d, e}}");
    set3>>"{{a,b,c},{d,e}}";
    EXPECT_EQ((set-set3).intoString(),"{a, b, c}");
    set-=set3;
    EXPECT_EQ(set.intoString(),"{a, b, c}");
    set4>>"{a,b,h,i}";
    EXPECT_EQ((set-set4).intoString(),"{c}");
}

TEST(SetTests, powerSet) {
    Set set,set2,set3,set4,set5,set6;
    set>>"{}";
    EXPECT_EQ(set.powerSet().intoString(),"{{}}");
    set2>>"{a}";
    EXPECT_EQ(set2.powerSet().intoString(),"{{a}, {}}");
    set3>>"{a, b}";
    EXPECT_EQ(set3.powerSet().intoString(),"{{a, b}, {a}, {b}, {}}");
    set4>>"{a, b, c}";
    EXPECT_EQ(set4.powerSet().intoString(),"{{a, b, c}, {a, b}, {a, c}, {a}, {b, c}, {b}, {c}, {}}");
    set5>>"{a, b, {c}}";
    EXPECT_EQ(set5.powerSet().intoString(),"{{a, b, {c}}, {a, b}, {a, {c}}, {a}, {b, {c}}, {b}, {{c}}, {}}");
    set6>>"{a, b, c, {c}}";
    EXPECT_EQ(set6.powerSet().intoString(),"{{a, b, c, {c}}, {a, b, c}, {a, b, {c}}, {a, b}, {a, c, {c}}, {a, c}, {a, {c}}, {a}, {b, c, {c}}, {b, c}, {b, {c}}, {b}, {c, {c}}, {c}, {{c}}, {}}");
}

TEST(SetTests, pop) {
    Set set;
    set.pop();
    EXPECT_EQ(set.intoString(),"{}");
    set.addElement("c");
    set.addElement("b");
    set.addElement("a");
    set.pop();
    EXPECT_EQ(set.intoString(),"{a, b}");
    set.addElement("b");
    set.pop();
    EXPECT_EQ(set.intoString(),"{a}");
    set.addElement("f");
    set.addElement("{f}");
    set.pop();
    EXPECT_EQ(set.intoString(),"{a, f}");
    set.pop();
    set.pop();
    EXPECT_EQ(set.intoString(),"{}");
}