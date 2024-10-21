std::lock_guard：

简单且轻量级。
只支持在构造时加锁，在析构时解锁。
不支持显式的解锁和重新加锁。

std::unique_lock：

更灵活，支持延迟锁定、显式解锁和重新加锁。
适用于需要更复杂锁管理的场景。
支持多种锁策略和转换。
选择哪一个取决于具体的需求。如果你需要简单的RAII风格的锁管理，std::lock_guard是一个很好的选择。如果你需要更多的控制和灵活性，那么std::unique_lock会更适合。

共享锁
- 读锁
  加锁时不允许其他线程加写锁，但允许其他线程加读锁
- 写锁
  加锁时不允许其他线程加读锁和写锁

防止死锁
1. 使用锁排序（Lock Ordering）
确保所有线程以相同的顺序获取锁。这可以防止循环等待的发生，从而避免死锁。

2. 超时检测（Timeout Detection）
在获取锁时使用超时机制，如果一个线程在尝试获取锁时超过了一定时间，可以认为可能存在死锁。

3. 图论方法（Graph Theory Methods）
使用资源分配图（Resource Allocation Graph, RAG）来检测死锁。资源分配图中的循环表示存在死锁。

4. 死锁检测算法（Deadlock Detection Algorithms）
使用操作系统或并发库提供的死锁检测算法。这些算法可以自动检测并报告死锁。

5. 动态分析工具（Dynamic Analysis Tools）
使用动态分析工具如Valgrind的Helgrind、ThreadSanitizer或其他静态分析工具来检测死锁。

6. 手动检查（Manual Inspection）
手动分析代码路径，确保不存在循环等待。这通常需要仔细的代码审查和测试。
