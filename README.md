# PGM-ExactInference

高志强老师的概率图模型精确推理作业，曾经使用 `c++20` 重构代码，现在使用 `c++23` 并且配合更专业的开发工具。

附带一些自己尝试编写的 `ranges`/`views` 算法。

经过很多次试验，对于给定数据的查询输出无误，其他情况未知。欢迎来 contribute 数据。

`master` 分支为最新版，x64 开发环境。

## ChangeLog

### v1.0.0 pre1

基于 XMake 构建，重构项目结构……

CLI 暂时去掉了。

### v0.5.0

进一步精简文件，统一 IO 接口。**彻底移除 xml 支持。**

### v0.4.0

在因子类的基础上重写团树法（`CliqueTreeMethod`），并增加团树类（`CliqueTree`）。

调整 `CliqueTree.yaml` 的键名 `variables`。

没有维护 `xml` 版，预计将彻底移除支持。

### v0.3.0

重写因子类、BeyasianNetwork、BNSumProduct。现在 `Factor` 类支持高效的因子存储和操作。可能可以利用 `valarray` 的一些操作进一步化简。

修改 `BayesianNetwork.yaml` 的存储结构，把变量信息和网络结点分离。

### v0.2.0

I/O 已从推理结构中分离，并加入异常处理，输入输出文件名可在 `ExactInferenceDlg_User.cpp` 中修改。

暂存到 `beta` 分支。

### v0.1.0

支持 YAML。所有 `.xml` 经过格式化，转为 utf8 格式，把该死的用于分隔值的 `、` 换成 `, `，且修改代码不再支持 `、，；`。

无 YAML 版暂存到 `xml-end` 分支。

## Dependency

- `vcpkg::ryml`：YAML 解析库。

### yaml 文件结构

#### `BayesianNetwork.yaml`

`variables` 为变量集，key 为结点 id，值含义比较显然。`nodes` 下，`parants` 为父结点数组，没有父结点的结点可以省略 `parants`，或置为 `null`；`CPT` 为概率分布顺序同 `xml` 版。

#### `CliqueTree.yaml`

相比 `.xml` 版更改了很多。`root` 为根结点 id。`variables` 为变量，需要使用 `numValues` 显式说明每个变量的取值数。

`cliques` 的 key 为团 id，`vars` 为团的变量，`vals` 按顺序给出 CPT，相比 `.xml` 不需要再给出具体因子。

`edges` 为团之间的无向边。每个数组中两个元素为边的端点 id。

【重要】要求团 id 为从 0 开始的连续自然数。

#### `BayesianNetwork_Query.yaml` / `CliqueTree_Query.yaml`

内容基本相同，只不过 CT 版不需要 `eliminate` 项。`marginal` 和 `given` 均以 `id: value` 形式给出因子。`eliminate` 为待消除因子 id 数组。

#### `Output.yaml` / `CliqueTree_Output.yaml`

内容应当完全一样，表示查询结果数组。

## 开发环境

## TODO（有生之年）

1. 使用轻量级 GUI 库，可视化图。
2. 增加从贝叶斯网生成团树的算法。
