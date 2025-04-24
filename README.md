# Philosopher

**프로젝트 개요**
Philosopher는 Dining Philosophers 문제를 구현한 교육용 프로젝트로, POSIX 스레드(pthread)와 뮤텍스(pthread_mutex)를 활용하여 철학자들이 포크를 공유하며 식사를 수행하는 동기화 로직을 학습합니다.

**프로젝트 의의**
- 스레드 생성과 관리: pthread를 이용한 동시성 제어 경험
- 뮤텍스 기반 자원 동기화: 교착 상태(Deadlock) 방지를 위한 뮤텍스 사용법 습득
- 타이밍 및 모니터링: gettimeofday 기반 시간 측정, starvation 모니터링 로직 구현
- 에러 처리 및 메모리 관리: 입력 검증, 동적 메모리 할당/해제, mutex 해제 절차 학습

## 주요 구현 모듈
- **입력 검증 (validate.c)**
  프로그램 실행 인자(argument)의 수와 값 유효성을 검사
- **초기화 (init.c)**
  Restaurant와 Philosopher 구조체를 할당·초기화하고, 뮤텍스를 생성
- **생명주기 (life.c, eating.c, time.c)**
  철학자의 THINK→EAT→SLEEP 순환 행동을 구현하고, 지정 시간 동안 동작
- **모니터링 (monitor.c)**
  개별 철학자의 생존 여부와 전체 종료 조건(full_goal 도달) 감시
- **유틸리티 (ft_for_atoitoa.c, ft_utils.c)**
  문자 숫자 변환(ft_itoa), 메모리 할당(ft_calloc) 등 보조 함수 제공
- **정리 및 해제 (clear_table)**
  스레드 종료 후 모든 뮤텍스 파괴 및 동적 메모리 해제를 수행

## 라이센스
이 프로젝트는 **Beerware License (Revision 42)**를 따릅니다.

```
THE BEER-WARE LICENSE (Revision 42)
As long as you retain this notice you can do anything with this stuff.
If we meet some day, and you think this stuff is worth it, you can buy me a beer in return.
```
