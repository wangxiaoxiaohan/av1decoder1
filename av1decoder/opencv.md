







### **一、基础形态学操作​**​

#### 1. ​**​腐蚀（Erosion）​**​

- ​**​原理​**​：通过滑动结构元素，仅当结构元素完全覆盖前景像素时保留中心像素。效果类似“收缩”前景区域

- ​**​作用​**​：
  
  - 去除细小噪声点
  - 分离相邻连接的物体
  - 细化物体边缘

- ​**​OpenCV函数​**​：
  
  ```python
  cv2.erode(src, kernel, iterations=1)
  ```

#### 2. ​**​膨胀（Dilation）​**​

- ​**​原理​**​：当结构元素与前景像素有重叠时，将中心像素设为前景。效果类似“扩张”前景区域

- ​**​作用​**​：
  
  - 填补物体中的小孔洞
  - 连接断裂的物体
  - 加粗物体边缘

- ​**​OpenCV函数​**​：
  
  
  
  ```python
  cv2.dilate(src, kernel, iterations=1)
  ```

---

### ​**​二、组合形态学操作​**​

#### 3. ​**​开运算（Opening）​**​

- ​**​原理​**​：先腐蚀后膨胀，数学表达式为：开运算=膨胀(腐蚀(A)) 
  
  

- ​**​作用​**​：
  
  - 去除白色小噪点（如椒盐噪声）
  - 平滑物体轮廓而不显著改变面积
  - 断开狭窄的连接部分

- ​**​OpenCV函数​**​：
  
  
  
  ```python
  cv2.morphologyEx(src, cv2.MORPH_OPEN, kernel)
  ```

#### 4. ​**​闭运算（Closing）​**​

- ​**​原理​**​：先膨胀后腐蚀，数学表达式为：闭运算=腐蚀(膨胀(A)) 

- ​**​作用​**​：
  
  - 填补黑色小孔洞
  - 连接邻近物体
  - 平滑物体边界

- ​**​OpenCV函数​**​：
  
  
  
  ```python
  cv2.morphologyEx(src, cv2.MORPH_CLOSE, kernel)
  ```

---

### ​**​三、高级形态学操作​**​

#### 5. ​**​形态学梯度（Morphological Gradient）​**​

- ​**​原理​**​：膨胀图与腐蚀图的差值，数学表达式为：梯度=膨胀(A)−腐蚀(A) 
  
  

- ​**​作用​**​：
  
  - 提取物体边缘轮廓
  - 突出图像中强度变化剧烈的区域

- ​**​OpenCV函数​**​：
  
  
  
  ```python
  cv2.morphologyEx(src, cv2.MORPH_GRADIENT, kernel)
  ```

#### 6. ​**​顶帽运算（Top Hat）​**​

- ​**​原理​**​：原始图像与开运算结果的差值，数学表达式为：顶帽=A−开运算(A) 

- ​**​作用​**​：
  
  - 提取比背景亮的细小区域（如文字、高光噪点）
  - 增强低频背景中的高频特征

- ​**​OpenCV函数​**​：
  
  
  
  ```python
  cv2.morphologyEx(src, cv2.MORPH_TOPHAT, kernel)
  ```

#### 7. ​**​黑帽运算（Black Hat）​**​

- ​**​原理​**​：闭运算结果与原始图像的差值，数学表达式为：黑帽=闭运算(A)−A 
  
  

- ​**​作用​**​：
  
  - 提取比背景暗的细小区域（如孔洞、阴影）
  - 检测图像中的暗纹或缺陷

- ​**​OpenCV函数​**​：
  
  python
  
  ```python
  cv2.morphologyEx(src, cv2.MORPH_BLACKHAT, kernel)
  ```

---

### ​**​四、结构元素（Structuring Element）​**​

- ​**​作用​**​：形态学操作的核心工具，决定操作的方向和尺度
  
  

- ​**​常见类型​**​：
  
  - `MORPH_RECT`：矩形（适合通用场景）
  - `MORPH_CROSS`：十字形（适合线状特征）
  - `MORPH_ELLIPSE`：椭圆形（适合圆形特征）

- ​**​创建方法​**​：
  
  python
  
  复制
  
  ```python
  kernel = cv2.getStructuringElement(shape, ksize)
  ```

---

### ​**​五、应用场景总结​**​

| 操作类型    | 典型应用场景             |
| ------- | ------------------ |
| 腐蚀/膨胀   | 去噪、边缘调整、物体分离/连接    |
| 开运算/闭运算 | 去除小噪点、填补孔洞、预处理分割结果 |
| 形态学梯度   | 边缘检测、医学图像血管提取      |
| 顶帽/黑帽   | 文档OCR增强、工业检测中的缺陷识别 |

# 魔方识别程序

```
// 自定义排序函数：先按y轴分三行，再按x轴排序
bool compareCenters(const Point& a, const Point& b) {
 int grid_height = 200; // 根据实际图像高度调整
 int row_a = a.y / (grid_height / 3);
 int row_b = b.y / (grid_height / 3);
 if (row_a == row_b) return a.x < b.x;
 return row_a < row_b;
}

vector detectCubeFace(Mat& image) {
 vector colors;
 Mat hsv, mask;

// 1. 预处理：转换颜色空间并提取黑色边框
cvtColor(image, hsv, COLOR_BGR2HSV);
inRange(hsv, Scalar(0, 0, 0), Scalar(180, 255, 40), mask);

// 形态学操作强化边缘
Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));、
//膨胀
dilate(mask, mask, kernel);

// 2. 查找轮廓
vector contours;
vector hierarchy;
findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

// 3. 筛选有效轮廓（四边形且面积足够大）
vector valid_contours;
vector centers;
for (const auto& cnt : contours) {
 double area = contourArea(cnt);
 if (area > 1000) {
 vector approx;
 approxPolyDP(cnt, approx, 0.02*arcLength(cnt, true), true);
 if (approx.size() == 4) {
 valid_contours.push_back(cnt);

// 计算中心点
 Moments m = moments(cnt);
 centers.emplace_back(int(m.m10/m.m00), int(m.m01/m.m00));
 }
}

}

// 4. 按位置排序轮廓
sort(centers.begin(), centers.end(), compareCenters);

// 重新关联排序后的轮廓
vector sorted_contours;
for (const auto& center : centers) {
 for (size_t i = 0; i < valid_contours.size(); ++i) {
 Moments m = moments(valid_contours[i]);
 Point cnt_center(int(m.m10/m.m00), int(m.m01/m.m00));
 if (cnt_center == center) {
 sorted_contours.push_back(valid_contours[i]);
 break;
 }
 }
}

// 5. 提取颜色信息
for (size_t i = 0; i < 9 && i < sorted_contours.size(); ++i) {
 Rect rect = boundingRect(sorted_contours[i]);
 Mat roi = image(rect).clone();

// 取中心区域（去除边缘干扰）
int margin = 5;
Rect inner_rect(margin, margin, rect.width-2*margin, rect.height-2*margin);
Mat color_region = roi(inner_rect);

// 计算平均颜色
Scalar mean_color = mean(color_region);
Mat color_mat(1, 1, CV_8UC3, mean_color);
cvtColor(color_mat, color_mat, COLOR_BGR2HSV);

// 颜色分类（示例阈值需要调整）
Vec3b hsv_color = color_mat.at(0, 0);
if (hsv_color[0] < 10) colors.emplace_back("Red");
else if (hsv_color[0] < 25) colors.emplace_back("Yellow");
else if (hsv_color[0] < 85) colors.emplace_back("Green");
else if (hsv_color[0] < 130) colors.emplace_back("Blue");
else colors.emplace_back("White");

}

return colors;

}

int main() {
 Mat image = imread("cube_face.jpg");
 if (image.empty()) {
 cout << "Failed to load image!" << endl;
 return -1;
 }

vector colors = detectCubeFace(image);

// 输出识别结果
cout << "识别到的颜色顺序：" << endl;
for (size_t i = 0; i < colors.size(); ++i) {
 cout << colors[i] << " ";
 if ((i+1) % 3 == 0) cout << endl;
}

return 0;

}

```
