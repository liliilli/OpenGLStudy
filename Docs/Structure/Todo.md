# Todo list

Updated 2018.05.23

- [ ] Font manager (5th)
  - [x] Resource manager 에서 Default 된 Font 가 없을 경우, 맨 첫번째로 받아온 것을 Default 로 하게 할 것.
  - [x] 리팩터링
  - [x] 확장 ASCII 이외 유니코드 문자 출력 구현
  - [ ] utf-8, utf-16 문자열을 저장하는 커스텀 스트링 컨테이너 구현
  - [ ] utf-8 저장 시, 런타임에 utf-16 문자열로 변환해서 저장하게끔 구현
  - [ ] 커스텀 스트링 컨테이너의 인덱스 참조, 붙이기, 등 구현.
  - [x] 확장 ASCII 이외 유니코드 문자 출력 테스트
    - [x] 테스트 씬 구현하기
    - [x] 다량의 텍스트 출력에 의한 퍼포먼스 저하 개선 (없는 듯한데?)
  - [x] 버그 : 8 pt 와 16 pt 이외의 폰트크기로 표시 시, 표시되지 않는 문제 수정. 우선 렌더러에서 엣지 뽑아낼 때 float floor 처리가 되서 일어나는 문제.
  - [x] 버그 : 개행 간격이 이상한 문제 수정. 및 개행 시마다 폰트가 타버리는 문제 수정. 폰트가 타버리는 문제는 개행 위치를 조정할 때 포인트가 소수점으로 내려가서 일어나는 것. 개행 간격이 이상한 것은 개행 문자를 null 로 잡아버려서 그런 것.
  - [ ] 버그 : 메모리 누수
  - [x] 버그 : IAlignable::Center 와 IAlignable::Right 가 출력이 되지 않고 Assertion 되는 문제. (길이를 저장해서 가지고 와야함)
- [x] Input manager (1st)
  - [x] Input setting 파일 manifest 을 통해서 불러오게 하기.
  - [x] 인풋 키 디버그 씬 구현 및 테스트
    - [x] 각 콜백에서 입력 값 캐쉬 저장 구현
  - [x] 키, 마우스 인풋 로그 출력
    - [x] 꾸밈없는 키보드 입력 폴링 출력.
- [ ] Object manager (6th)
  - [x] 코드 스타일에 맞춰서 리팩터링
  - [x] ~~씬 내부 오브젝트 Update 처리를 Component 별로 개선~~
    - [x] ~~검증 후에 처리를 해야할 것 같음. (성능 비교 후 처리)~~
    - 하지 않기로 함. 오히려 더 복잡해짐. 그리고 한 오브젝트마다 컴포넌트가 연속적으로 존재하기 때문에 지역성이 더 파괴될 것 같음.
  - [x] 에러 핸들링 검증
  - [x] /// @todo Improve performance object destruction.
  - [ ] 버그 : 메모리 누수
- [x] Object (2nd)
  - [x] 생명주기 디버그 및 테스트 씬 만들기
    - [x] ~~Bug?~~ Object 가 Disabled 되었을 때, 해당 Object 의 스크립트의 타이머는 어떻게 되는가?
  - [x] Object 가 Disable 된다고 하더라도 Pause 을 사용해서 스크립트의 타이머를 일시정지하게 하면 된다.  즉, 사양임.
    - [x] Camera Orthogonal 시, Z 가 안보이는 문제?
  - [x] 사양임. Orthogonal 은 기본 rear 와 far 이 0 으로 되어 있음.
    - [x] EmptyObject (말 그대로 텅 빈 오브젝트) 를 만들어서 빌트인으로 제공해야 함.
    - [x] Bug : Texture2DAtlas Index 반영 안되는 문제 (되는데?)
  - [x] 생명주기 루틴 구현
    - [x] scene Instantiate 부분 수정
    - [x] object Instantiate 부분 수정
  - [x] 생명주기 Initiate() 루틴 구현
    - [x] Scene 구현
    - [x] Object 구현
    - [x] 코드 리팩터링 및 공통 부분 별도의 파일로 코드 옮기기.
  - [x] 생명주기 Start() 루틴 구현
  - [x] 생명주기 Disabled() 루틴 구현
    - [x] Enabled, Disabled 는 Object 자체의 Enable, Disable 전환에 따라 실행됨.
  - [x] 생명주기 Enabled() 루틴 구현
  - [x] 생명주기 Destroy() 루틴 구현
    - [x] 파괴 리스트에 담긴 후에, 진짜로 힙 릴리즈가 되기 전에 Destroy() 함수 실행.
- [ ] etc (7th)
  - [ ] 오브젝트 주기 다시 확인할 것.
  - [x] Release mode 동작 테스트+'
  - [x] VAO, VBO 와 같은 메쉬 버퍼 컨테햣 이너 내부 관리자 만들기. 및 RAII 로 메모리 누수 처리하면서...
    - [x] 3D 는 아직 하지 말기. 2D 쿼드만 처리하거나, 아니면 2D 형태만 할 수 있도록. 하지만 2D 메쉬도 결국 3D 이기 때문에... 등등.
  - [x] TimerManager 1프레임 일시정지, 재개 테스트
  - [x] 리소스 파일 구조 바꾸기
  - [x] ~~*Bug* : Rendering layer 가 제대로 정렬되지 않는 것 같음.~~ 됐는데?
  - [x] Phitos 가 아닌 Assertion 파일 및 의존성 지우기
  - [x] `Component/Internal/flag.h` 의존성을 `Phitos` 로 옮기기
    - 냅두자...
  - [x] `Input` 에서, `Stick` 과 `non-stick` 이 아직 구분이 되지 않아서 계속 쭈욱 이동함.
  - [x] 스크립트 도중에 `Script` 을 생성해버리면, `Initiate` 가 호출되지 않는 문제점 발생.
  - [ ] `input.meta` 의 키 바인딩을 숫자가 아닌 따로 설정된 키 스트링으로 하게 할 것.
    - 예를 들어서 256 대신에 "esc" 라던가, 265 대신에 "arrow_up" 이라던가...
    - 다만 그렇게 할 경우에는 페이지를 만들어서 어떤 키가 어떤 스트링인지를 명확하게 해야할 필요가 있음.
    - 또한 이 키를 바인딩하기 위해서 `input` 쪽에서 파싱 처리를 해줘야함.
  - [x] `CObject` 및 `Object` `Scene` 에서 이름 생성하는 방법 같게 하기.
  - [x] `CObject` 및 `Obejct` `Scene` 에서 Destroy object 시, 어드레스 비교로 지우게 끔 하기.
    - 우선 DestroyChild 에서 manager::object::Destroy 을 할 때 자기 오브젝트에서 루트를 만들어서 지우게끔 함.
    - 문제는 `DestroyChild` 의 ref 을 받는 버전에선 리턴값으로 성공 아니면 실패를 내놔야하는데 지금은 `object::Destroy` 가 `void` 라서 성공 실패 여부 확인이 안됨.
  - [x] `CScene` 의 오브젝트 이름 충돌을 피할 것.
  - [x] `Animator` 리팩터링 완료.
- Object, Component 의 Enable, Disable 처리 기능. (8th 및 onEnable disable 이랑 관계 有)
  - [x] Object 부분
    - [x] 기초
    - [x] 전파
  - [x] Component 부분
  - [ ] Object 을 생성하자 마자 바로 Deactivate 할 경우, 좌표가 이상하게 전파되는 것 같음. 예를 들면 상위 오브젝트가 포지션 전파를 했는데, `Deactivate` 된 곳에서는 이를 받지 않아서 좌표가 이상하게 된다던가.
- [ ] OPGS16 내부 통용 타입 만들기
  - [ ] Vector2, Vector3, Vector4
    - [x] Vector2
    - [x] VectorI2
    - [x] Vector3
    - [x] VectorI3
    - [ ] Vector4
  - [ ] 1차원 메모리 공간을 갖는 2차원 배열 Matrix, 혹은 Dim2Vector
    - Dim2Vector 을 사용해서 Matrix 을 쓰면 되지 않을까?
    - 구현하지 말 것. 고정형 2차원 벡터를 쓰게 되면 부딪히는 부분이 너무 많다.
  - [x] `<random>` 및 `<chrono>`  을 정의하지 않고도 바로 랜덤을 쓸 수 있도록 제공하는 `SRandom` 네임스페이스.
  - [ ] 회전 값을 담고 있는 `Quaternion` 클래스
  - [x] `DClamp` 클래스
- [x] 샘플 게임으로 테트리스 만들어보기. (GAME BOY) (지금 컵게임 만들고 있음)

### ~~0.1.5~~ 0.2.0 버전 구현사항

오브젝트 주기 다시 확인할 것.

* 스크립트는 자기 자체가 비활성화가 되면 OnEnable, OnDisable 플래그를 자기가 품고 있어야 한다.

Mesh (3rd)

- [ ] 3D Mesh obj, fbx, collada 불러오기 구현
- [ ] VAO, VBO 등의 지오메트리 버퍼 저장소 구현
- [ ] 메모리 누수 잡기

Physical (4th)

- [ ] **리팩터링.**
- [ ] **Kinetic, Dynamic 및 스위치에 따른 루틴 구현**
- [x] **bullet library 적용 (x64 Debug)**
- [ ] **새로운 Rigidbody (bullet library 을 적용하는) 을 만들어서 적용.**
  - [ ] **충돌박스만 선으로 표시하기**
  - [ ] 그 후에 bullet3 을 사용해서 (bulllet3 역시 3축 월드 xyz 을 사용.) 정보를 가져와서 쓰도록 하면 어떨까 싶음. 포지션 갱신은 Model Matrix 로...

Input Manager

- [ ] 마우스 버튼 입력 구현
  - [x] 가상 마우스 출력
  - [ ] 고정 텍스쳐를 입힌 가상 마우스 출력
- [ ] 마우스 버튼 입력 테스트
  - [x] 일반 로그 출력 테스트.
  - [ ] 실제 오브젝트와 상호작용 테스트
- [ ] 마우스 위치 이동.
- [ ] 마우스 객체 생성자, 소멸자 붙이기.
- [x] 마우스 위치 이동 화면 스케일 보정 및 축 좌표 전환 보정.
- [ ] 마우스 위치 이동 총 테스트 및 검증.
- [ ] 파티클 시스템 구현

1. **`Object` 의 Parent 을 바로 알 수 있도록 하기**
2. **`Object` 의 Parent 을 옮기는 기능. 여기서 월드 좌표를 그대로 반영할지 아니면 새로 좌표를 부모에 대해서 갱신하게 할 지도 구현**
3. **`Bullet3` 적용**
4. `3D` 메쉬 적용
5. 빛 바인딩 시스템 구현 및 검증.
6. `inline static constexpr const char*` 을 따로 매크로 정의로 간편하게 해당 오브젝트의 이름을 적용해볼 수 있도록 잡 기능을 추가함.
7. 옵저버 패턴을 사용한 `Scene` 에서 발행하는 Message 수신 기능.
8. **스크립트의 타이머를 해당 오브젝트가 deactive 될 때, 스크립트가 디액티브 될 때 등에 맞춰서 일시정지를 자동으로 하게 해야함. 아님... 그냥 onDisable() 에서 직접 구현하게 하던가? 흠.**
9. **쉐이더 오류 버그 수정해야 함.**

* [x] 해상도를 256x224, 320x240, ~~400x240~~ 으로 늘리기로 결정. 두 가지 모드중에서 하나를 쓸 수 있고 스케일링은 그대로 적용한다. 640x480 도 가능하나, 스케일링이 불가함. **`FixedFunctionResolution`**
  * 400x240 은 실장을 할까?... 음... 슈팅게임에는 엄청 좋겠다만.
  * 실장을 하자.
* [ ] 비트맵 폰트도 실장할 수 있도록 하기.
* [ ] 샘플 게임 만들어보기. 샘플 게임은...  뭘로 하지? ㅋㅋㅋㅋ 이번엔 한달 정도로 잡아서 만들어볼까? 한달도 길다. 우얀다.

### 0.2.1 버전 구현 사항

1. `Joystick` 인풋 기능 구현.
   2. 