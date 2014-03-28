
#ifndef AUTOMAT_H
#define AUTOMAT_H

class nod_automat {
public:
    int f_state ;
    vector <nod_automat*> neigh[27];
    nod_automat(int x = 0) : f_state(x) {}

} ;


class automat {
private:
    nod_automat *T;
    vector <nod_automat*> end_states;

    const int LAMBDA;
    int convert(char x) {
        return int(x - 'a');
    }

    void insert(nod_automat *t, string s , int i) {
        if (s.size() == i) {
            t -> f_state = 1;
            end_states.push_back(t);
            return ;
        }
        int f = convert(s[i]);
        t -> neigh[f].push_back(new nod_automat());
        insert(t -> neigh[f][ t -> neigh[f].size() - 1], s, i + 1);
    }
    vector <nod_automat*> get_end_states() {
        return end_states;
    }
    nod_automat *get_begin() {
        return T;
    }
public:
    automat(string S) : LAMBDA(26) {
        T = new nod_automat();
        insert(T, S, 0);
    }
    int See(string S) {

        queue < pair <int, nod_automat*> > Q;
        Q.push(make_pair(0, T));

        map <pair <int, nod_automat *> , int> mark;
        while (!Q.empty()) {
            pair <int, nod_automat*> A = Q.front() ;
            Q.pop();

            if (A.second -> f_state && A.first == S.size())
                return 1;

            if (A.first == S.size()) {
//			cerr << S[A.first] << " ";

                for (int i = 0; i < A.second -> neigh[LAMBDA].size(); ++i) {
                    if (mark[make_pair(A.first, A.second -> neigh[LAMBDA][i])]) {
                        continue;
                    }
                    Q.push( make_pair (A.first, A.second -> neigh[LAMBDA][i]) );
                    mark[make_pair(A.first, A.second -> neigh[LAMBDA][i])] = 1;
                }
            }
            else {

                for (int i = 0 ; i < A.second -> neigh[ convert(S[A.first]) ].size(); ++i) {
                    if (mark[make_pair(A.first + 1,A.second -> neigh[ convert(S[A.first])][i])])
                        continue;
                    Q.push( make_pair (A.first + 1, A.second -> neigh[ convert(S[A.first]) ][i]));
                    mark[ make_pair( A.first + 1, A.second -> neigh [convert (S[A.first])][i] ) ] = 1;
                }
                for (int i = 0; i < A.second -> neigh[LAMBDA].size(); ++i) {
                    if (mark[ make_pair( A.first, A.second -> neigh[LAMBDA][i])]) {
                        continue;
                    }
                    Q.push( make_pair(A.first, A.second -> neigh[LAMBDA][i]));
                    mark[ make_pair( A.first, A.second -> neigh[LAMBDA][i])] = 1;
                }
            }
        }
        return 0;
    }

// concat <=> (A1 + A2) <=> A1A2
    void concat(automat &Y) {
        nod_automat *A2 = Y.get_begin();

        for (int j = 0; j < end_states.size(); ++j) {
            end_states[j] -> f_state = 0;
            end_states[j] -> neigh[LAMBDA].push_back(A2);
        }
        end_states = Y.get_end_states();
    }
// A1 | A2
    void unite(automat &Y) {
        nod_automat *A2 = Y.get_begin();

        T -> neigh[LAMBDA].push_back(A2);
        vector <nod_automat*> tmp = Y.get_end_states();

        for (int i = 0; i < tmp.size(); ++i)
            end_states.push_back(tmp[i]);
    }
//	A*
    void star() {
        for (int i = 0; i < end_states.size(); ++i) {
            T -> neigh[LAMBDA].push_back(end_states[i]);
            end_states[i] -> neigh[LAMBDA].push_back(T);
        }
        end_states.push_back(T);
        T -> f_state = 1;
    }

};
#endif
/*
int main() {
	automat A("a"), B("b"), C("c");
	A.concat(B); A.unite(C);
	A.star();

	while(1) {
		string str;
		cin >> str;
		cout << A.See(str) << "\n";
	}
	return 0;
}
*/
