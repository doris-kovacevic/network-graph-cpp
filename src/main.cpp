#include <iostream>
#include <fstream>
#include <string>
#include <limits>


//#include "../h/GraphPtOne.h"
#include "../h/GraphPtTwo.h"

using namespace std;

bool greska()
{
	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Uneli ste nepravilan oblik parametra" << endl;
		return true;
	}
	return false;
}
int main() {
	Graph* graph = new Graph();
	while (true)
	{
		cout << "Izaberite jednu od sledecih komandi:" << endl;
		cout << "0: Formiranje mreze" << endl;
		cout << "1: Dodavanje korisnika u mrezu" << endl;
		cout << "2: Uklanjanje korisnika iz mreze" << endl;
		cout << "3: Dodavanje veze izmedju dva korisnika" << endl;
		cout << "4: Uklanjanje veze izmedju dva korisnika" << endl;
		cout << "5: Ispis reprezentacije mreze (grafa)" << endl;
		cout << "6: Lajkovanje objave" << endl;
		cout << "7: Nalazenje najvece komponente u mrezi" << endl;
		cout << "8: Najverovatniji put od jednog ka drugom korisniku" << endl;
		cout << "9: Odredjivanje k-te najuticajnije osobe" << endl;
		cout << "10: Brisanje mreze iz memorije" << endl;
		cout << "11: Prekid rada" << endl;
		int option;
		cin >> option;
		if(greska())
			continue;
		if (option == 11)
			break;
		switch (option)
		{
			case 0:
			{
				cout << "Unesite naziv fajla: ";
				string name;
				cin >> name;
				deleteGraph(graph);
				graph = createGraph(name);
				break;
			}
			case 1:
			{
				cout << "Unesite id korisnika: ";
				string id;
				cin >> id;
				addNode(graph, id);
				break;
			}
			case 2:
			{
				cout << "Unesite id korisnika: ";
				string id;
				cin >> id;
				deleteNode(graph, id);
				break;
			}
			case 3:
			{
				cout << "Unesite id korisnika, id korisnika sa kojim je formirana veza i jacinu veze: ";
				string id1, id2;
				double weight;
				cin >> id1;
				cin >> id2;
				cin >> weight;
				if (greska())
					break;
				addBranch(graph, id1, id2, weight);
				break;
			}
			case 4:
			{
				cout << "Unesite id korisnika i id korisnika sa kojim je postojala veza: ";
				string id1, id2;
				cin >> id1;
				cin >> id2;
				deleteBranch(graph, id1, id2);
				break;
			}
			case 5:
			{
				printGraph(graph);
				break;
			}
			case 6:
			{
				cout << "Unesite id korisnika i id korisnika cija je objava lajkovana: ";
				string id1, id2;
				cin >> id1;
				cin >> id2;
				Like(graph, id1, id2);
				break;
			}
			case 7:
			{
				MaxComponent(graph);
				break;
			}
			case 8:
			{
				cout << "Unesite id pocetnog i id krajnjeg korisnika: ";
				string id1, id2;
				cin >> id1;
				cin >> id2;
				MostLikelyPath(graph, id1, id2);
				break;
			}
			case 9:
			{
				cout << "Unesite prirodan broj k: ";
				int k;
				cin >> k;
				if (greska())
					break;
				KthInfluence(graph, k);
				break;
			}
			case 10:
			{
				deleteGraph(graph);
				graph = new Graph();
				break;
			}
			default:
			{
				deleteGraph(graph);
				break;
			}
		}
		cout << endl;
	}
	deleteGraph(graph);
}
