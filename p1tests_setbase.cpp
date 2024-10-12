#include <gtest/gtest.h>
#include "bset.hpp"

TEST(SetBaseTests, add) {
    Set set;
    set>>"{a, c, b,{e,d}}";
    set.addElement("f");
    EXPECT_EQ(set.intoString(),"{a, b, c, f, {d, e}}");
    set.addElement("{x,y}");
    EXPECT_EQ(set.intoString(),"{a, b, c, f, {d, e}, {x, y}}");
}

TEST(SetBaseTests, remove) {
    Set set;
    set>>"{a, c, b,{e,d}}";
    set.removeElement("c");
    EXPECT_EQ(set.intoString(),"{a, b, {d, e}}");
    set.removeElement("{d,e}");
    EXPECT_EQ(set.intoString(),"{a, b}");
    set.removeElement("w");
    EXPECT_EQ(set.intoString(),"{a, b}");
    set.removeElement("{v,w}");
    EXPECT_EQ(set.intoString(),"{a, b}");
    set.removeElement("{a,b}");
    EXPECT_EQ(set.intoString(),"{a, b}");
    set.removeElement("{a}");
    EXPECT_EQ(set.intoString(),"{a, b}");
}

TEST(SetBaseTests, equals) {
    Set set,set2,set3;
    string setString="{a, c, b,{e,d}}";
    set>>setString;
    set2>>setString;
    set3>>"{a}";
    EXPECT_TRUE(set==set2);
    EXPECT_FALSE(set==set3);
    EXPECT_FALSE(set2==set3);
    EXPECT_FALSE(set!=set2);
    EXPECT_TRUE(set!=set3);
    EXPECT_TRUE(set2!=set3);
}

TEST(SetBaseTests, contains) {
    Set set;
    set>>"{a, c, b,{e,d}}";
    EXPECT_TRUE(set["a"]);
    EXPECT_TRUE(set["b"]);
    EXPECT_TRUE(set["c"]);
    EXPECT_TRUE(set["{d,e}"]);
    EXPECT_FALSE(set["{{d,e}}"]);
    EXPECT_FALSE(set["{{{d,e}}}"]);
    EXPECT_FALSE(set["{a, b, c, {d, e}}"]);
    EXPECT_FALSE(set["{a, b, c}"]);
    EXPECT_FALSE(set["abc"]);
}

TEST(SetBaseTests, empty) {
    Set set;
    EXPECT_TRUE(set.empty());
    set>>"{a}";
    EXPECT_FALSE(set.empty());
}

TEST(SetBaseTests, cardinality) {
    Set set;
    set>>"{a, c, b,{e,d}}";
    EXPECT_EQ(set.cardinality(),4);
    set.addElement("f");
    EXPECT_EQ(set.cardinality(),5);
    set.addElement("{x,y}");
    EXPECT_EQ(set.cardinality(),6);
    set.removeElement("a");
    EXPECT_EQ(set.cardinality(),5);
    set.removeElement("a");
    EXPECT_EQ(set.cardinality(),5);
    set.removeElement("{d,e}");
    EXPECT_EQ(set.cardinality(),4);
    set.removeElement("{d,e}");
    EXPECT_EQ(set.cardinality(),4);
}

TEST(SetBaseTests, getElement) {
    Set set;
    set>>"{a, c, b,{e,d}}";
    EXPECT_EQ(set.getElement(0),"a");
    EXPECT_EQ(set.getElement(1),"b");
    EXPECT_EQ(set.getElement(2),"c");
    EXPECT_EQ(set.getElement(3),"{d, e}");
    EXPECT_EQ(set.getElement(-42),"");
    EXPECT_EQ(set.getElement(2147483647),"");
    set.addElement("f");
    EXPECT_EQ(set.getElement(3),"f");
    EXPECT_EQ(set.getElement(4),"{d, e}");
}

TEST(SetBaseTests, numbers) {
    Set set;
    set>>"{a, c, b,{e,d}}";

    EXPECT_EQ(set.simpleElementsNumber(),3);
    EXPECT_EQ(set.setsNumber(),1);
    EXPECT_EQ(set.simpleElementsNumber()+set.setsNumber(),set.cardinality());

    set.addElement("f");
    EXPECT_EQ(set.simpleElementsNumber(),4);
    EXPECT_EQ(set.setsNumber(),1);
    EXPECT_EQ(set.simpleElementsNumber()+set.setsNumber(),set.cardinality());

    set.addElement("{x,y}");
    EXPECT_EQ(set.simpleElementsNumber(),4);
    EXPECT_EQ(set.setsNumber(),2);
    EXPECT_EQ(set.simpleElementsNumber()+set.setsNumber(),set.cardinality());

    set.removeElement("{x,y}");
    set.removeElement("{d,e}");
    EXPECT_EQ(set.simpleElementsNumber(),4);
    EXPECT_EQ(set.setsNumber(),0);
    EXPECT_EQ(set.simpleElementsNumber()+set.setsNumber(),set.cardinality());

    set.removeElement("a");
    set.removeElement("b");
    set.removeElement("c");
    set.removeElement("f");
    EXPECT_EQ(set.simpleElementsNumber(),0);
    EXPECT_EQ(set.setsNumber(),0);
    EXPECT_EQ(set.simpleElementsNumber()+set.setsNumber(),set.cardinality());
}