//     /ᐠ˶˶ᐟ\
//   (=•ㅅ < )
//  |￣∪∪￣|
//  |＿求AC＿|
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
using vvi=vector<vi>;
using vvl=vector<vl>;

// 牌的点数映射
inline int rankMap(char c) {
    if (c >= '2' && c <= '9') return c - '0';
    if (c == 'T') return 10;
    if (c == 'J') return 11;
    if (c == 'Q') return 12;
    if (c == 'K') return 13;
    if (c == 'A') return 14;
    return 0;
}

// 花色转数字
inline int suitMap(char c) {
    if (c == 'C') return 0;
    if (c == 'D') return 1;
    if (c == 'H') return 2;
    if (c == 'S') return 3;
    return -1;
}

// 牌
struct Card {
    int rank, suit;
    bool operator<(const Card& other) const {
        if (rank != other.rank) return rank < other.rank;
        return suit < other.suit;
    }
    bool operator==(const Card& other) const {
        return rank == other.rank && suit == other.suit;
    }
};
inline int getID(const Card& c) {
    return c.rank * 4 + c.suit;
}

struct HandType {
    int type;
    int cmp[5];
    HandType(int t = 0) : type(t) {
        memset(cmp, 0, sizeof(cmp));
    }
    // 大于
    bool operator>(const HandType& other) const {
        if (type != other.type) return type > other.type;
        for (int i = 0; i < 5; i++) {
            if (cmp[i] != other.cmp[i]) return cmp[i] > other.cmp[i];
        }
        return false;
    }
};

// 顺子
pair<bool, int> isStraight(int r[5], int out[5]) {
    int tmp[5];
    memcpy(tmp, r, sizeof(tmp));
    sort(tmp, tmp + 5);
    bool normal = true;
    for (int i = 1; i < 5; i++) {
        if (tmp[i] != tmp[i-1] + 1) {
            normal = false;
            break;
        }
    }
    if (normal) {
        for (int i = 0; i < 5; i++) out[i] = tmp[4 - i];
        return {true, 0};
    }
    // A2345
    if (tmp[0]==2 && tmp[1]==3 && tmp[2]==4 && tmp[3]==5 && tmp[4]==14) {
        out[0]=5;out[1]=4;out[2]=3;out[3]=2;out[4]=1;
        return {true, 0};
    }
    return {false,0};
}


HandType getHandType(const vector<Card>& base, Card add) {
    int r[5], s[5];
    int ptr = 0;
    for (auto& c : base) {
        r[ptr] = c.rank;
        s[ptr] = c.suit;
        ptr++;
    }
    r[4] = add.rank;
    s[4] = add.suit;

    // 统计花色同花
    bool flush = true;
    int su = s[0];
    for (int i = 1; i < 5; i++) if (s[i] != su) {flush = false; break;}

    // 统计点数频次
    int freq[15] = {0};
    for (int i = 0; i < 5; i++) freq[r[i]]++;

    int st_cmp[5];
    auto [st, _] = isStraight(r, st_cmp);

    HandType res;
    // 同花顺
    if (flush && st) {
        if (st_cmp[0] == 14) {
            res.type = 9;
            memcpy(res.cmp, st_cmp, sizeof(st_cmp));
            return res;
        } else {
            res.type = 8;
            memcpy(res.cmp, st_cmp, sizeof(st_cmp));
            return res;
        }
    }
    // 四条
    int four = -1;
    for (int i = 2; i <=14; i++) if(freq[i]==4) four=i;
    if (four != -1) {
        res.type =7;
        res.cmp[0]=four;
        for(int i=2;i<=14;i++) if(freq[i]==1) res.cmp[1]=i;
        return res;
    }
    // 葫芦
    int three=-1, two=-1;
    for(int i=14;i>=2;i--){
        if(freq[i]==3) three=i;
        if(freq[i]==2) two=i;
    }
    if(three!=-1 && two!=-1){
        res.type=6;
        res.cmp[0]=three; res.cmp[1]=two;
        return res;
    }
    // 同花
    if(flush){
        res.type=5;
        int tmp[5];
        memcpy(tmp, r, sizeof(tmp));
        sort(tmp,tmp+5,greater<int>());
        memcpy(res.cmp, tmp, sizeof(tmp));
        return res;
    }
    // 普通顺子
    if(st){
        res.type=4;
        memcpy(res.cmp, st_cmp, sizeof(st_cmp));
        return res;
    }
    // 三条
    if(three!=-1){
        res.type=3;
        res.cmp[0]=three;
        int p=1;
        int tmp[5]; int pt=0;
        for(int x:r) if(x!=three) tmp[pt++]=x;
        sort(tmp,tmp+pt,greater<int>());
        for(int i=0;i<pt;i++) res.cmp[p++]=tmp[i];
        return res;
    }
    // 两对
    vi pairs, singles;
    for(int i=14;i>=2;i--){
        if(freq[i]==2) pairs.push_back(i);
        else if(freq[i]==1) singles.push_back(i);
    }
    if(pairs.size()==2){
        res.type=2;
        res.cmp[0]=pairs[0];
        res.cmp[1]=pairs[1];
        res.cmp[2]=singles[0];
        return res;
    }
    // 一对
    if(pairs.size()==1){
        res.type=1;
        res.cmp[0]=pairs[0];
        int p=1;
        int tmp[5]; int pt=0;
        for(int x:r) if(x!=pairs[0]) tmp[pt++]=x;
        sort(tmp,tmp+pt,greater<int>());
        for(int i=0;i<pt;i++) res.cmp[p++]=tmp[i];
        return res;
    }
    // 高牌
    res.type=0;
    int tmp[5];
    memcpy(tmp, r, sizeof(tmp));
    sort(tmp,tmp+5,greater<int>());
    memcpy(res.cmp, tmp, sizeof(tmp));
    return res;
}

vector<Card> allCards;
void initCards() {
    string ranks = "23456789TJQKA";
    string suits = "CDHS";
    for (char r : ranks) {
        for (char s : suits) {
            Card tmp;
            tmp.rank = rankMap(r);
            tmp.suit = suitMap(s);
            allCards.push_back(tmp);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    initCards();
    int T;
    cin >> T;
    while (T--) {
        vector<Card> myCards(4), oppCards(4);
        bool vis[60] = {false}; 
        string s;
        // 我方4张
        for (int i = 0; i < 4; i++) {
            cin >> s;
            myCards[i].rank = rankMap(s[0]);
            myCards[i].suit = suitMap(s[1]);
            vis[getID(myCards[i])] = true;
        }
        // 对手4张
        for (int i = 0; i < 4; i++) {
            cin >> s;
            oppCards[i].rank = rankMap(s[0]);
            oppCards[i].suit = suitMap(s[1]);
            vis[getID(oppCards[i])] = true;
        }
        // 筛选可用暗牌
        vector<Card> available;
        for (auto& c : allCards) {
            if (!vis[getID(c)]) available.push_back(c);
        }
        bool iWinAll = true;
        bool oppCanWin = false;
        int sz = available.size();

        for (int i = 0; i < sz; i++) {
            if (oppCanWin) break; 
            Card opAdd = available[i];
            bool iCanWin = false;
            bool oppWinAll = true;

            for (int j = 0; j < sz; j++) {
                if (j == i) continue;
                Card myAdd = available[j];
                HandType myT = getHandType(myCards, myAdd);
                HandType opT = getHandType(oppCards, opAdd);
                if (myT > opT) {
                    iCanWin = true;
                    oppWinAll = false;
                    break; 
                } else if (!(opT > myT)) {
                    oppWinAll = false;
                }
            }
            if (oppWinAll) oppCanWin = true;
            if (!iCanWin) iWinAll = false;
        }
        if (iWinAll) {
            cout << "WoYaoYanPai\n";
        } else if (oppCanWin) {
            cout << "GeiWoCaPiXie\n";
        } else {
            cout << "PaiMeiYouWenTi\n";
        }
    }
    return 0;
}