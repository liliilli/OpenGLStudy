# 파티클 시스템 구현

> 2018-08-02 문서 작성

## 문서

> 언리얼쪽을 참고해보자.

파티클 `Particle` 은 `Point sprite` 라고도 하며, 메쉬가 아니라 점에 텍스쳐를 입혀서 빌보딩 등으로 만드는 시스템이다. 메쉬를 사용해서 거기에 쉐이딩을 입혀 파티클과 비슷하지만 좀 더 사실적인 효과를 구현할 수도 있지만, 파티클의 경우에는 가장 기본적이지만 아주 간편하게 효과를 구현할 수 있다는 점, 그리고 성능을 보다 덜 잡아먹는다는 점에서 우수하다.

![EmitterCallout.png](https://docs.unrealengine.com/portals/0/images/Engine/Rendering/ParticleSystems/Cascade/EmitterCallout.png) 

## 제안 & 구현 사항

1. 파티클을 표현할 텍스쳐가 필요하다. 또한 텍스쳐를 출력할 쉐이더도 필요하다.
2. 한 입자를 출력하는데 필요한 시간, 혹은 시간 당 출력 양이 필요하다.
3. 각 입자의 생명주기가 필요하다.
4. 초기 사이즈, 생명 주기 당 사이즈, 
   초기 속도, 생명 주기 당 속도, 
   초기 틴트 컬러, 생명주기 당 틴트 컬러, 
   초기 스케일, 생명 주기 당 스케일,
   초기 회전, 생명 주기 당 회전
5. 어떻게 파티클을 출력할 것인가 (방사, 등등..) 의 Spawn 역시 필요하다.
6. 각 입자의 생명 시간.

의 요소가 필요하다. 

1. 만약에 파티클마다 오브젝트 형태로 힙을 할당하게 된다면, 오브젝트 풀은 필수로 필요하다. 메모리는 많이 잡아먹을 지 언정 구현은 쉽다.
2. 또는, `OpenGL` 의 인스턴싱을 활용해서 속성 등을 `uniform` 배열과 현재 살아있는 파티클의 수를 쉐이더로 보내서 렌더링하게 한다. 이 방법은 오브젝트 풀이 필요 없지만, 구현이 쓸데없이 복잡하다.

#### 그래서?

일단 쉬운 방법으로 구현을 하고, 성능이 마땅하지 않을 때만 2의 방법을 고려해본다. 그런데 딱히 성능 차이가 있지는 않을 것 같다...

* 렌더러는 한 효과 당 하나만 바인딩한다. 각 파티클 오브젝트는 부모쪽의 (이미터) 렌더러를 가져와서 쓴다. 
* 파티클은 `CCObject` 이... 지 않다. 파티클은 `CComponent` 이며 파티클 안에 `Emitter` 와 `Renderer` 등의 부수 컴포넌트가 존재한다. 왜 `CCobject`가 아니냐면, `CCObject` 는 `Update()` 가 될 수도 있다.
* `CParticleRenderer` 는 `Emitter` 을 생성해서 반환하는 것, `Emitter` 의 위에서 말한 속성, 텍스쳐 등등을 변경하는 것이 가능하도록 API 을 제공한다.
* 파티클 컴포넌트 내부의 각 `Emitter` 는 오브젝트 풀을 가지며, 실제 렌더링을 할 수 있도록 한다.
* 만약 파티클을 담는 오브젝트가 지워졌을 경우에는, 소멸된 오브젝트의 파이널 포지션을 가진 채 임시 파티클 오브젝트 리스트에 들어가, 애니메이션이 다 끝날 때까지 기다린 후 소멸시킨다.
* 파티클의 렌더링은 마지막에 이루어지며, `Depth test` 등을 무시하고 `Blend` 을 항상 킨다. 주체는 파티클 컴포넌트이며 파티클 컴포넌트는 `pfRender()` 와 같은 함수에서 각 이미터에 `pfRender()` 와 같은 실질 렌더 함수를 돌려서 렌더링을 하도록 한다.
* 애니메이션이 끝난 각 오브젝트는 소멸하지 않고 Deactivate 되서 풀의 마지막에 보관된다.

#### 또한?

* 만약에 오브젝트 삭제되서 `Renderer` 가 이동되는 게 아니라, 오브젝트는 살아있지만 `Emitter` 가 삭제가 되버리면 어떻게 되는가? 도중에 렌더링을 끊어야 하는가? 아니면 `Emitter` 의 마지막 파티클이 끝날 때 까지 다른 곳에 보관해 뒀다가 `IsSleep` 이 True 이면 죽여야 하는가?

#### 테스트 구현하기

1. 

## 결과

#### 2018-08-03 PM 11:55

우선 가장 기본이 되는 `_internal::CParticleEmitter` 와 `CParticleRenderer` 의 뼈대를 만들었다. `Module` 의 구조를 생각해본 건데, `Emitter` 는 `Module` 을 컴포지션으로 가지고 있으며 이미터에서 지원하는 모듈이 없다면, 일반 Emitter 의 포인터 혹은 레퍼런스를 가져와서 사용한다.