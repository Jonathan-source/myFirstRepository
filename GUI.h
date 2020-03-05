#ifndef GUI_H
#define GUI_H


class GUI {

public:
	GUI(const GUI &other) = delete;
        GUI& operator=(const GUI &other) = delete;

	GUI(sf::RenderWindow& window);
	virtual ~GUI();

	// Methods
	void draw(sf::RenderTarget& window);



private:
    	Frame_infoBar;
        Frame_selectBar;
	Frame_buildBar;
	
	Label_Population;
	Label_Food;
	Label_Wood;
	Label_Stone;
	Label_Gold;
	Label_Metal;

	// Methods
	void initInfoBar();
        void initSelectingBar();
        void initBuildBar();

       	void unSelect();
        void unBuild();
        void setBuild();
};
	

// CPP

void GUI::update(sf::Time dT)
{
        switch(_status)
        {
        case Status::Selecting :
	break;
	case Status::UnSelect :
	break;
	case Status::Building :
	break;
	}
}
