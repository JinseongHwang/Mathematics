/*  컴퓨터공학과 1723940 황진성 
	확률 및 통계 중간대체 과제 05번 */

#include <iostream>
#include <vector>
#include <utility>
using namespace std;

typedef pair<int, int> pii; 
int n, k, cnt = 0;
vector<int> divisor; // n의 약수들을 저장
vector<pii> curr_calc; // 연산을 수행할 k개의 값들을 저장
// first: 피연산자, second: divisor벡터에서 피연산자의 index number

void init() { // 실행 속도 단축
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
}
void print_vector() { // 약수의 목록과 개수를 출력
	cout << "\n >>> 약수 목록 >>>\n";
	for (int i = 0; i < divisor.size(); ++i) {
		cout << divisor[i] << " ";
	} cout << "\n총: " << divisor.size() << "개\n\n";
}
bool meet_conditions() { // k개의 정수의 곱이 n이 맞는지 판별
	int result = 1;
	for (int i = 0; i < k; ++i) {
		result *= curr_calc[i].first;
		if (result > n) break;
	}
	if (n == result) return true;
	else return false;
}
void dfs(int depth) { // DFS기법을 이용해서 순서대로 탐색
	int start = depth - 1 >= 0 ? curr_calc[depth - 1].second : curr_calc[0].second;
	// start :: curr_calc 배열에서 index가 앞인 것보다 값이 작으면 안되고 뒤인 것보다 크면 안되기 때문 -> 중복방지
	for (int i = start; i < divisor.size(); ++i) {
		curr_calc[depth].first = divisor[i];
		curr_calc[depth].second = i;
		if (depth < k - 1) dfs(depth + 1);
		if (depth == k - 1 && meet_conditions()) {
			for (int d = 0; d < curr_calc.size(); ++d) // 출력
				cout << curr_calc[d].first << " ";
			cout << "\n"; cnt++;
		}
	}
}
int main() {
	init();
	cout << " >>> n값을 입력하세요: "; cin >> n;
	cout << " >>> k값을 입력하세요: "; cin >> k;

	/* 벡터 divisor에 양의 고유약수 값들을 저장 */
	for (int i = 2; i <= n / 2; ++i) {
		if (n % i == 0) 
			divisor.push_back(i); 
	} print_vector(); // 약수 목록 출력

	curr_calc.resize(k); // random access를 위한 메모리 할당
	for (int i = 0; i < k; ++i) { // 초기값 설정
		curr_calc[i].first = divisor[0];
		curr_calc[i].second = 0;
	}

	dfs(0);

	cout << "만족하는 방법의 수: " << cnt << "\n";
	return 0;
}
