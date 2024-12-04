# Interpolation Search {Result Image}
![](/16-interpolationSearch(1).png)
![](/16-interpolationSearch(2).png)
![](/16-interpolationSearch(3).png)

---

# 결과 분석 
### ▪ Interpolation Search가 Binary Search보다 적게 비교하는 이유를 설명
**Interpolation Search**
데이터가 균일하게 분포되어 있을 때, 예상 위치를 계산하여 검색

![](/interpolation.png)

*low와 high는 현재 탐색 범위의 시작과 끝 인덱스*
배열의 값이 선형적으로 증가한다고 가정하여, 목표값의 예상 위치를 비율로 계산한다.
만약 목표값이 배열에서 특정 구간에 집중되어 있다면, 탐색 속도가 더 빠르다.

탐색 위치를 예측적으로 점프하므로, 필요한 비교 횟수가 줄어든다.
보간탐색은 평균적으로 O(log N)의 시간 복잡도를 보인다.

**Binary Search**
배열의 중간 위치를 기준으로 탐색

정렬된 배열에서 중간 요소를 확인한 뒤, 목표값과 비교해 탐색 범위를 절반으로 줄이는 과정이다.
탐색 범위 축소는 등분(반씩 나누는) 방식으로 이루어지므로, 데이터 분포에 관계없이 O(log N)의 시간복잡도를 가진다.
하지만 데이터가 균일하게 분포되지 않은 경우에도 중간값 기준으로 탐색하므로, 비교 횟수가 최적화되지 못할 수 있다.
(목표값이 끝쪽에 있을수록 탐색 범위를 줄이는데 더 많은 단계가 필요)
