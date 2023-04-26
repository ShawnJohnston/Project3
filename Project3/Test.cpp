//#define CATCH_CONFIG_MAIN
//#include "catch.hpp"
//#include <catch2/catch_session.hpp>
//
//#include "Menu.h"
//
//TEST_CASE("File IO") {
//	ifstream file;
//	file.open("cats.csv");
//
//	string line;
//	string item;
//
//	vector<Cat*> collection;
//
//	if (!file.eof()) {
//		while (getline(file, line)) {
//			
//
//			stringstream ss(line);
//
//			int order, id;
//			string age, gender, size, coat, breed;
//
//			int counter = 0;
//			while (getline(ss, item, ',')) {
//				if (item == "order") {
//					break;
//				}
//
//				switch (counter) {
//				case 0:
//					order = stoi(item);
//					break;
//				case 1:
//					id = stoi(item);
//					break;
//				case 2:
//					break;
//				case 3:
//					break;
//				case 4:
//					age = item;
//					break;
//				case 5:
//					gender = item;
//					break;
//				case 6:
//					size = item;
//					break;
//				case 7:
//					coat = item;
//					break;
//				case 8:
//					breed = item;
//				default:
//					if (item.substr(0, 7) == " 'full'") {
//
//						int trimLength = 0;
//						for (size_t i = item.length() - 1; i > 0; i--) {
//							char index = item.at(i);
//							if (index < 48 || index > 57) {
//								trimLength++;
//							}
//							else {
//								break;
//							}
//						}
//						string cleanLink = item.substr(10, item.length());
//						cleanLink = cleanLink.substr(0, cleanLink.length() - trimLength);
//
//						Cat* cat = new Cat(order, id, age, gender, size, coat, breed, cleanLink);
//						collection.push_back(cat);
//					}
//					break;
//				}
//
//				counter++;
//			}
//		}
//	}
//	file.close();
//}
//
//int main(int argc, char* argv[]) {
//	// your setup ...
//
//	int result = Catch::Session().run(argc, argv);
//
//	// your clean-up...
//
//	return result;
//}