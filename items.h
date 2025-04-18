#include <string>


class Item{
    int id;
    int rarity;
    std::string name;
    //Pre and post item indicates when they activate (before or after your turn). Active items can be used on command. Outside items are used outside of combat
    bool preItem;
    bool postItem;
    bool activeItem;
    bool outsideItem;

    int fluteCharge;
    //bool curActive;

    public:
        Item();

        ~Item();

        void setRarity();
        void setIDAndName(int rarity);
        void display() const;
        void generateItem();
        int getId();
        std::string getName();
        bool getPreItem();
        bool getPostItem();
        bool getActiveItem();
        bool getOutsideItem();
        int getFluteCharge();
        void setFluteCharge(int decreaseAmount);

        //This override is strictly for testing purposes
        void itemOverride(std::string testName, int testId, bool testPre, bool testPost, bool testOut, bool testActive);
};