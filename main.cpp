#include "d.h"

#define NAME_LEN 256
#define INFO_LEN 1024

void printHelp ();


int main()
{

	try {
		FILE           *f;
		f = fopen("test.txt", "r");
		BTree		tree;
		char		key       [256], name[NAME_LEN], info[INFO_LEN];
		int		n         , i = 0;
		cout << "\n+------------+\n";
		cout << "| Database D |\n";
		cout << "+------------+\n\n";
		while (1) {
			cout << "> ";
			cin >> key;

			if (strcmp(key, "add") == 0) {
				name[0] = info[0] = key[0] = '\0';
				cout << "Enter student's name: ";

				while (i == 0 || i == 1 || (name[i - 1] != '\n' && i < NAME_LEN)) {
					scanf("%c", &name[i]);
					i++;
				}

				name[i - 1] = '\0';
				for (int j = 0; j < i - 1; j++)
					name[j] = name[j + 1];

				i = 0;
				cout << "Enter number of this student's group (without spaces): ";
				cin >> n;
				cout << "Enter any information about this student: ";

				while (i == 0 || i == 1 || (info[i - 1] != '\n' && i < INFO_LEN)) {
					scanf("%c", &info[i]);
					i++;
				}

				info[i - 1] = '\0';
				i = 0;
				Student		s      (name, n, info);
				tree.add(s, n);
				tree.showtree();
				cout << endl;	/* tree.print(tree.root()); */
			}
			if (strcmp(key, "search") == 0) {
				name[0] = key[0] = '\0';
				cout << "Enter student's name: ";

				while (i == 0 || i == 1 || (name[i - 1] != '\n' && i < NAME_LEN)) {
					scanf("%c", &name[i]);
					i++;
				}

				name[i - 1] = '\0';

				for (int j = 0; j < i - 1; j++)
					name[j] = name[j + 1];

				i = 0;
				cout << "Enter number of this student's group (without spaces): ";
				cin >> n;
				cout << endl;
				BTreeNode      *res;

				if (tree.search(tree.root(), n, &res)) {
					int		m         , t;
					for (m = res->n - 1, t = 0; m - t > -1;) {
						if (res->value[(int)((t + m) / 2)].x == n) {
							if (!res->value[(int)((t + m) / 2)].y.search(name))
								cout << "student not found\n" << endl;
							break;
						}
						if (res->value[(int)((t + m) / 2)].x > n)
							m = (int)(m + t) / 2 - 1;
						if (res->value[(int)((t + m) / 2)].x < n)
							t = (int)(m + t) / 2 + 1;
					} cout << endl;
				} else
					cout << "student not found\n" << endl;

			}
			if (strcmp(key, "search_by_num") == 0) {
				key[0] = '\0';
				cout << "Enter number of this student's group (without spaces): ";
				cin >> n;
				cout << endl;
				BTreeNode      *res;

				if (tree.search(tree.root(), n, &res)) {
					int		m         , t;
					for (m = res->n - 1, t = 0; m - t > -1;) {
						if (res->value[(int)((t + m) / 2)].x == n) {
							res->value[(int)((t + m) / 2)].y.printFront();
							break;
						}
						if (res->value[(int)((t + m) / 2)].x > n)
							m = (int)(m + t) / 2 - 1;
						if (res->value[(int)((t + m) / 2)].x < n)
							t = (int)(m + t) / 2 + 1;
					} cout << endl;
				} else
					cout << "students not found\n" << endl;
			}
			if (strcmp(key, "del_by_num") == 0) {
				key[0] = '\0';
				cout << "Enter number of group (without spaces): ";
				cin >> n;
				tree.del(n);
				tree.showtree();
				cout << endl;
			}
			if (strcmp(key, "del") == 0) {
				name[0] = key[0] = '\0';
				cout << "Enter student's name: ";

				while (i == 0 || i == 1 || (name[i - 1] != '\n' && i < NAME_LEN)) {
					scanf("%c", &name[i]);
					i++;
				}

				name[i - 1] = '\0';

				for (int j = 0; j < i - 1; j++)
					name[j] = name[j + 1];

				i = 0;
				cout << "Enter number of this student's group (without spaces): ";
				cin >> n;
				tree.Delete(name, n);
			}
			if (strcmp(key, "test") == 0) {
				if (f == NULL)
					throw(Exception("file test.txt not found"));
				key[0] = '\0';

				while (!feof(f)) {
					fscanf(f, "%s%d%s", name, &n, info);
					Student		s      (name, n, info);
					tree.add(s, n);
					//cout << name << endl;
				} tree.showtree();
			}
			if (strcmp(key, "q") == 0)
				break;
			if (key[0] != '\0')
				printHelp();
		}

		tree.clear(tree.root());

	} catch(Exception a) {
		cout << a.reason << endl;
	}

	return 0;
}

void
printHelp()
{

	cout << "+---------------------------Database D--------------------------+\n";
	cout << "| 'add' -                   add student's name and group number |\n";
	cout << "| 'search' -      search for a student by name and group number |\n";
	cout << "| 'search_by_num' -       search for a students by group number |\n";
	cout << "| 'del' -              removal of information about the student |\n";
	cout << "| 'del_by_num' -         removal of information about the group |\n";
	cout << "| 'q' -                       quit                              |\n";
	cout << "| 'test' -                    test                              |\n";
	cout << "+---------------------------------------------------------------+\n";
	cout << endl;
}
