#include "Libraries/color.hpp"
#include <functional>
#include <stdlib.h>
class Renderer {
public:
	static std::vector<std::string> dieOne;
	static std::vector<std::string> dieTwo;
	static std::vector<std::string> dieThree;
	static std::vector<std::string> dieFour;
	static std::vector<std::string> dieFive;
	static std::vector<std::string> dieSix;

	using colorFunction = std::function<dye::colorful<std::string>(const std::string&)>;
	static void drawPixel(colorFunction color) {
		std::cout << color("##");
	}
	static void drawRect(colorFunction color, int width, int length) {
		for (int i = 0; i < length; i++) {
			for (int j = 0; j < width; j++) {
				std::cout << color("##");
			}
			std::cout << std::endl;
		}
	}
	static void drawSquare(colorFunction color, int length) {
		drawRect(color, length, length);
	}
	static void clear() {
		system("cls");
	}

	static void drawDie(const std::vector<std::string>& die) {
		for (int i = 0; i < die.size(); i++) {
			for (int j = 0; j < die[i].size(); j++) {
				if (die[i][j] == '0')std::cout << dye::bright_white_on_bright_white("#");
				else if (die[i][j] == '1')std::cout << dye::black_on_black("#");
			}
			std::cout << std::endl;
		}
	}

	static const std::vector<std::string>& die(size_t n) {
		switch (n) {
		case 1: return dieOne; break;
		case 2: return dieTwo; break;
		case 3: return dieThree; break;
		case 4: return dieFour; break;
		case 5: return dieFive; break;
		case 6: return dieSix; break;
		default: return dieOne; break;
		}
	}





	static void drawDieRow(const std::vector<std::string>& die1,
		const std::vector<std::string>& die2,
		const std::vector<std::string>& die3) {

		int size = die1[0].size();
		std::ostream& out = std::cout;

		for (int i = 0; i < die1.size(); i++) {
			out << dye::black_on_black("##");

			for (int d = 0; d < 3; ++d) {
				const std::vector<std::string>& die = (d == 0 ? die1 : d == 1 ? die2 : die3);

				for (int j = 0; j < size; ++j) {
					char c = die[i][j];
					if (c == '0') out << dye::bright_white_on_bright_white("#");
					else if (c == '1') out << dye::black_on_black("#");
				}

				out << dye::black_on_black("##");
			}

			out << '\n';
		}
	}

	static void drawDie() {
		drawDie(dieOne);
		std::cout << std::endl;
		drawDie(dieTwo);
		std::cout << std::endl;
		drawDie(dieThree);
		std::cout << std::endl;
		drawDie(dieFour);
		std::cout << std::endl;
		drawDie(dieFive);
		std::cout << std::endl;
		drawDie(dieSix);
		std::cout << std::endl;
	}
};

std::vector<std::string> Renderer::dieOne = { "0000000000",
											  "0000000000",
											  "0000110000",
											  "0000000000",
											  "0000000000", };

std::vector<std::string> Renderer::dieTwo = { "0000000000",
											  "0110000000",
											  "0000000000",
											  "0000000110",
											  "0000000000"};

std::vector<std::string> Renderer::dieThree = { "0000000000",
												"0110000000",
												"0000110000",
												"0000000110",
												"0000000000", };

std::vector<std::string> Renderer::dieFour = { "0000000000",
											   "0110000110",
											   "0000000000",
											   "0110000110",
											   "0000000000" };

std::vector<std::string> Renderer::dieFive =  { "0000000000",
												"0110000110",
												"0000110000",
												"0110000110",
												"0000000000", };

std::vector<std::string> Renderer::dieSix =  { "0000000000",
											   "0110110110",
											   "0000000000",
											   "0110110110",
											   "0000000000" };
