# BP-Nonogram-Solver
Nonogram Solver by Belief Propagation

## 입력/출력
입력은 한 조건 내에선 띄어쓰기, 조건 간에는 줄 바꿈으로 구분되며, 1행의 조건(가로 조건)부터 n행의 조건, 1열의 조건(세로 조건)부터 m열의 조건 순으로 입력.

■/□으로 색칠 여부 출력.

<img src="https://user-images.githubusercontent.com/35063338/184306723-19c7cda9-9728-4f9d-b974-63992799d9cb.png" width="300" height="250"/> 

## 실행 과정
<img src="https://user-images.githubusercontent.com/35063338/184304382-3b94837c-cfe3-4a1d-9848-cc3ff91bb6e1.png" width="600" height="300"/>  

Factor Graph는 칸에 해당하는 변수 노드와 조건에 해당하는 함수 노드로 구성

<img src="https://user-images.githubusercontent.com/35063338/184304758-cc755018-f89f-490b-a2a7-bbd311f11aa7.png" width="900" height="150"/>  

함수는 위와 같이 조건 만족 여부를 반환함.

<img src="https://user-images.githubusercontent.com/35063338/184304611-a79402a4-e7c3-4f6a-9692-9935191f084d.png" width="500" height="300"/>  

Sum-product Algorithm에 따라 유도해낸 수식으로, 위와 같은 메세지를 주고 받아 전체가 수렴하면, 칸 별로 0/1 결정.

## 결과 그래프
n에 따른 수렴 속도 차이

<img src="https://user-images.githubusercontent.com/35063338/184303662-121320e3-b30d-49f0-9380-4322e5869d7f.png" width="500" height="300"/>  
<img src="https://user-images.githubusercontent.com/35063338/184303725-c0a47552-f559-40aa-a870-7aafb37c66ca.png" width="500" height="300"/>  

