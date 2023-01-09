//============================================================================
// Name        : notenberechnung.cpp
// Author      : Rn11
// Version     :
// Copyright   : © 2022 Rn11
// Description : Notenberechnungsprogramm
//============================================================================

#include <iostream>
// Header fuer subject-map
#include <map>
using namespace std;

// Prototypen der Funktionen zum Einlesen, Auswerten und Ausgeben der Daten
void input(double (&)[9]);
double calculate(double (&)[9]);
void output(double);

/*
 * Eine map der Schulfaecher. Diese wird benutzt, um die Fachbezeichnung den
 * Indizes des Noten-Arrays zuzuordnen.
 */
std::map<int, std::string>  subjects = {
		{ 0, "Planen von Anlagen und Arbeitsprozessen" },
		{ 1, "Montage und Inbetriebnahme" },
		{ 2, "Instandhaltung" },
		{ 3, "Fremdsprachliche Kommunikation" },
		{ 4, "Wirtschafts- und Betriebslehre" },
		{ 5, "Deusch/Kommunikation" },
		{ 6, "Religionslehre" },
		{ 7, "Sport/Gesundheitsfoerderung" },
		{ 8, "Politik/Gesellschaftslehre" }
};

int main() {
	// Array zur Speicherung der 9 eingegebenen Noten eines Schuelers
	double grades[9];
	// Funktionsaufruf zum Eingeben der Noten
	input(grades);
	/*
	 * Hier wird die calculate-Funktion aufgerufen, welche die Berufsschulabschlussnote berechnet.
	 * Der Rueckgabewert der Funktion wird als Parameter fuer die output-Funktion benutzt, die im Anschluss
	 * aufgerufen wird. Damit wird die Berufsschulabschlussnote formatiert ausgegeben.
	 */
	output(calculate(grades));

	/*
	 * Die Praeprozessordirektive #ifdef wird genutzt, um zu pruefen, ob es sich um ein Windows-System handelt.
	 * Andernfalls kann "system("pause")" nicht aufgerufen werden. Falls nicht, wird der Befehl "sleep" verwendet,
	 * der Bestandteil der GNU Coreutils ist, welche Hauptbestandteil von Linux-Systemen ist.
	 * Unter Verwendung der Praeprozessordirektive kann der Praeprozessor, abhaenging von der Ausfuerungsumgebung,
	 * entsprechenden Code von der Kompilierung ausschliessen bzw. auswaehlen.
	 */
	#ifdef _WIN32
		system("pause");
	#else
		system("sleep 5");
	#endif
	return 0;
}

/*
 *  Funktion zum Einlesen der Benutzereingaben / Noten eines Schuelers
 *
 * Es werden die Noten für 9 Faecher eingelesen. Die Eingabe wird zuerst in einer Variable zwischengespeichert,
 * damit geprueft werden kann, ob der eingegebene Wert im Gueltigkeitsbereich liegt. Falls nicht,
 * wird die Eingabe fuer das Fach so lange wiederholt, bis der Wert gueltig ist.
 *
 * Im Folgenden wird pass-by-reference benutzt. Dadurch wird das Array direkt veraendert, anstatt es zu kopieren.
 */
void input(double (&grades)[9]) {
	double userinput;

	// Wiederhole Vorgang für alle 9 Noten
	for (int i = 0; i < 9; i++) {
		// Eingabe der Note. Der Fachname wird aus der map "schulfaecher" bezogen
		cout << "Geben Sie die Note für das Fach " << subjects.find(i)->second << " ein: ";
		cin >> userinput;

		// Pruefe Nutzereingabe auf Gueltigkeit und wiederhole ggf. Eingabe bis der Wert gueltig ist
		while (userinput < 1 || userinput > 6) {
			cout << "Falsche Eingabe, bitte eine gueltige Note eingeben: ";
			cin >> userinput;
		}
		// Wenn der Wert gueltig ist, schreibe diesen ins Array
		grades[i] = userinput;
		cout << endl;
	}
}

/*
 * Funktion zur Berechnung der Berufsschulabschlussnote.
 * Alle 9 Noten werden mit dem Notengewchtungsfaktor multipliziert,
 * das Ergebnis daraus addiert und durch den summierten Notengewichtungsfaktor dividiert.
 */
double calculate(double (&grades)[9]) {
	double grade_sum = 0;
	uint divisor_sum = 0;

	// Iteriere alle Elemente des Arrays / alle Noten
	for (int subject_id = 0; subject_id < 9; subject_id++) {
		/*
		 * Wenn die ersten 3 Noten verrechnet werden, inkrementiere Divisor um 2 statt um 1
		 * aufgrund der Stundenanzahl. Aufgrund der Aufgabenstellung wird der Divisor somit immer 12 betragen.
		 */
		switch (subject_id+1) {
		case 1:
		case 2:
		case 3:
			divisor_sum +=2;
			// Multipliziere Note mit Gewichtungsfaktor 2
			grade_sum += (2*grades[subject_id]);
			break;

			// Default Block: Wird ausgefuert, wenn Notengewichtungsfaktor 1 verwendet werden soll
		default:
			// Inkrementiere Divisor (Gesamtnotengewichtungsfaktor) um 1
			divisor_sum++;
			// Summiere Notenwert
			grade_sum += grades[subject_id];
			break;
		}
	}
	// Teile Notenwertsumme durch summierten Notengewichtungsfaktor und gebe Wert an caller
	return grade_sum/divisor_sum;
}

/*
 *  Funktion fuer die Ausgabe. Konvertiert den Parameter zu einem String und
 *  kuerzt die Laenge auf eine Nachkommastelle (drei Zeichen). Gibt anschliessend
 *  die Note aus.
 *
 *  Alternative Loesungsansaetze wie printf ... %.1f, final_grade - 0.005 oder
 *  setprecision scheinen zu runden oder zumindest das Ergebnis zu beeinflussen
 *  (2.75 --> 2.8, 2.666 -> 2.7)
 */
void output(double final_grade) {
	// Konvertierung zu string
	string output = to_string(final_grade);
	// Auf 3 Zeichen kuerzen
	output.resize(3);
	cout << "Die Berufsschulabschlussnote betraegt: " << output;
}
