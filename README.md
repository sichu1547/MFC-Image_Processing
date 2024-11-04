# 다양한 OpenCV 라이브러리 실습 및 Defect Detection
이 프로젝트는 OpenCV와 MFC를 활용하여 다양한 이미지 처리 및 결함 검출 기능을 구현한 프로그램입니다.

## 기능 목록
아래 기능 목록에서 원하는 기능을 클릭하면 상세한 설명을 볼 수 있습니다.

1. [ImageFiltering](#ImageFiltering)
2. [ImageInverse](#ImageInverse)
3. [ImageRotation](#ImageRotation)
4. [Mirroring](#Mirroring)
5. [ImageResize](#ImageResize)
6. [ImageSave](#ImageSave)
7. [AddRandomDefect](#AddRandomDefect)
8. [DetectDefect](#DetectDefect)
9. [DetectShiftedDefects](#DetectShiftedDefects)
---

### ImageFiltering
`ImageFiltering` 함수는 입력 이미지를 다양한 필터를 통해 처리하여 이미지의 품질을 개선하거나 특정 특징을 강조합니다. 대표적인 필터로는 `Gaussian, Median, Bilateral` 필터가 있으며, 각 필터는 노이즈 제거, 경계선 강조 등 목적에 따라 다르게 적용됩니다.

`Gaussian Filter`: 이미지의 고주파 노이즈를 제거하기 위해 사용됩니다. 이 필터는 가우시안 분포를 기반으로 인접 픽셀의 가중 평균을 구하여 노이즈를 제거합니다.


`Median Filter`: 비선형 필터링 기법으로, 잡음 제거에 효과적입니다. 특히 엣지가 유지되어야 하는 경우 유용하며, 입력 픽셀의 중간값을 대체하여 노이즈를 억제합니다.


`Bilateral Filter`: 가우시안 블러와 유사하지만, 엣지를 보존하는 필터입니다. 인접한 픽셀뿐만 아니라 값이 유사한 픽셀만 포함시켜 처리합니다.

상황에 따라 다양한 필터를 적용해야 하며 코드에는 `Gaussian Filter`를 사용합니다.

### ImageInverse
`ImageInverse` 함수는 입력 이미지의 픽셀 값을 반전하여 출력합니다. Image GrayScale의 최대값인 255에서 현재 픽셀 값의 차이로 계산합니다.

모든 픽셀에 대하여 접근이 필요하므로 SIMD 병렬처리 연산으로 수행합니다.

### ImageRotation
`ImageRotation` 함수는 이미지를 주어진 각도만큼 회전시킵니다. 이미지를 회전함으로써 다양한 관점에서 분석하거나 특징을 추출하는 데 도움을 줍니다.

회전은 원점에 대한 선형 변환으로, 각 픽셀의 좌표를 회전 행렬에 곱하여 새로운 좌표로 이동시킵니다. 회전 행렬은 각도에 따라 X와 Y 좌표를 각각 변환합니다.

포인트를 Center 중심으로 잡고 `getRotationMatrix2D`를 통해 행렬을 생성하고 `warpAffine` 함수를 사용하여 Rotation을 수행합니다. 회전 각도가 직각을 이루지 못하면 빈공간이 생기고 `Scalar(0, 0, 0)` 으로 채워줍니다.

### Mirroring
`Mirroring` 함수는 이미지의 가로 또는 세로 축을 기준으로 이미지를 대칭 변환합니다. 주로 데이터 증강에 사용되며, 객체의 대칭성을 학습시키는 데 유용합니다.

`상하반전` : 이미지의 절반을 접근해야 하기 때문에 `_mm256` SIMD 명령어를 활용하여 효율적으로 반전을 수행하며, 중복된 메모리 접근을 최소화합니다.

`좌우반전` : `flip` 함수를 통해 이미지의 좌우를 반전합니다.

상하반전 구현에 사용한 SIMD 명령어는 픽셀을 모두 가로로 읽기 때문에 제약없이 사용이 가능했지만, 좌우반전은 세로를 기준으로 변경해야 했고 `flip` 내장함수를 찾아 간단히 수행할 수 있었습니다.

### ImageResize
`ImageResize` 함수는 이미지의 크기를 조정하여 해상도를 변경합니다.

`Scale` 수치를 UI를 통해 입력받고  `dScale > 1 ? INTER_LINEAR : INTER_AREA` 조건을 통해 확대 시 선형 보간을, 축소 시 Area 기반 보간을 사용하여 품질을 최대한 유지합니다.

### ImageSave
`ImageSave` 함수는 처리된 이미지를 특정 파일 형식으로 저장합니다. 사용자가 지정한 경로에 파일을 저장하여 이후에 재사용할 수 있도록 합니다. `saveDlg.DoModal() == IDOK`를 통해 경로를 입력받아 `imwrite`를 수행합니다.

### AddRandomDefect
`AddRandomDefect` 함수는 이미지에 결함을 랜덤하게 추가합니다. 각 결함의 위치와 개수, 패턴은 랜덤으로 결정되며, 결함을 인위적으로 추가하여 결함 검출 함수의 성능을 테스트하는데 사용합니다.

UI를 통해 생성할 Defect의 개수를 입력받고 `srand((unsigned int)time(nullptr));` 랜덤 시드를 통해 위치와 크기, Scalar 정의 후 `rectangle`, `circle`, `line`중 하나의 패턴을 선택하여 Defect을 추가합니다. 추가된 Defect의 위치는 `vector<Rect>`에 저장 후 `if ((newDefect & defect).area() > 0)` AND연산을 통해 공통 영역 여부를 확인하여 중복을 방지합니다.

### DetectDefect
`DetectDefect` 함수는 입력 이미지와 기준 이미지를 비교하여 결함이 있는지 확인합니다. 결함이 있는 부분을 탐지하여 해당 위치를 표시합니다.

결함 검출은 픽셀 단위 비교를 통해 수행됩니다. 기준 이미지와 입력 이미지의 차이를 계산하여 차이가 특정 임계값 이상일 경우 결함으로 간주합니다. 이는 일반적으로 이미지의 픽셀값을 차분하거나 특정 알고리즘을 통해 차이를 계산하여 결함을 판단합니다.

일반적인 경우 이미지의 같은 위치를 참조하여 `abs(imgdata1 - imgdata2)`로 비교하지만 내장함수인 `absdiff`를 통해 이미지의 차이를 계산합니다. 

`threshold` 함수로 임계값을 설정하고 두 이미지의 차이가 임계값을 초과하는지 알아내고 이를 통해 결함이 더 잘보이게 유도합니다. `findContours` 함수는 이진화된 이미지에서 외곽선을 찾아 벡터의 형태로 저장합니다. 마지막으로 `for (const auto& contour : contours)` const를 사용하여 contour가 변경될 수 없게 처리한 뒤, 설정한 결함 판단기준에 따라 최종 결과를 처리합니다.

### DetectShiftedDefects
`DetectShiftedDefects` 함수는 결함이 기준 위치에서 이동했을 때에도 이를 탐지합니다. 이는 미세한 이동이 있는 경우에도 결함을 정확히 감지할 수 있도록 합니다. 

함수의 목적은 조명이나 환경적인 요인에 따라 `동일 위치의 픽셀을 비교할 수 없을 경우`를 가정하여 테스트합니다. 이미지 정합 알고리즘을 사용하여 기준 이미지와 입력 이미지를 위치 정렬한 후 결함을 탐지합니다. 이동된 결함을 감지하기 위해 상관 함수나 특징점 매칭을 통해 이미지 위치를 맞춘 뒤, 결함 위치를 파악합니다.
```
Mat shiftedDefect;
Mat shiftMatrix1 = (Mat_<double>(2, 3) << 1, 0, iShiftX, 0, 1, iShiftY);
warpAffine(defImg, shiftedDefect, shiftMatrix1, defImg.size());
```
+ shiftMatrix1로 시프트 행렬을 설정하고 `warpAffine` 함수를 사용하여 결함 이미지를 지정된 수치만큼 이동하여 새로운 시프트 이미지를 생성합니다.

```
Ptr<ORB> orb = ORB::create();
vector<KeyPoint> keypoints1, keypoints2;
Mat descriptors1, descriptors2;
orb->detectAndCompute(orgImg, Mat(), keypoints1, descriptors1);
orb->detectAndCompute(shiftedDefect, Mat(), keypoints2, descriptors2);
```
+ ORB 알고리즘을 사용하여 원본 이미지와 시프트된 결함 이미지의 특징점과 디스크립터를 추출합니다. 이러한 특징점은 이미지에서 뚜렷한 패턴을 나타내며, 이후 매칭 과정에서 사용됩니다.

+ `BFMatcher matcher(NORM_HAMMING)` : 브루트 포스 매처(BFMatcher)를 사용하여 두 이미지의 디스크립터를 비교하고 매칭을 수행합니다. NORM_HAMMING는 이진 디스크립터의 거리를 측정하는 데 사용됩니다.

+ 매칭된 점의 거리를 기준으로 최대 거리와 최소 거리를 찾아냅니다. 좋은 매칭점은 최소 거리의 2배 이하인 매칭점을 필터링하여 수집합니다. 그 후 좋은 매칭점을 기반으로 각 이미지에서 대응하는 점들을 모아 변환 행렬을 추정하고 `estimateAffinePartial2D` 함수로 두 점 집합 간의 변환을 추정합니다. 이후 시프트에 대한 보정을 필요시 수행할 수 있습니다.

+ 변환 행렬을 가지고 `warpAffine`를 사용하여 align을 수행한 이미지를 생성합니다. 이후 `DetectDefect`함수와 동일하게 픽셀 차이를 구하고 이진화를 수행합니다.

### 주의 
시프트연산을 통해 이미지의 손실이 생기게 됩니다. 관심 영역을 설정하고 이진화를 수행한 이미지에 맞춰 잘라내야 합니다. 평행이동을 수행한 이미지는 조명 또는 환경적인 요인에 따른 변화를 가정한 것이므로 실제로는 시프트된 이미지가 생기더라도 손실되는 영역은 생기지 않습니다.