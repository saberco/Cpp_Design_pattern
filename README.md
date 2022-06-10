# Cpp_Design_pattern
# 一句话总结设计模式
----
## 创造型模式
创建型模式（Creational Pattern）对类的实例化过程进行了抽象，能够将软件模块中对象的创建和对象的使用分离。为了使软件的结构更加清晰，外界对于这些对象只需要知道它们共同的接口，而不清楚其具体的实现细节，使整个系统的设计更加符合单一职责原则。

模式名称|总结
-------|-----
工厂模式|工厂方法在父类中提供一个创建对象的方法，允许子类决定实例化对象的类型
抽象工厂模式|抽象工厂能创建一系列相关的对象，而无需指定其具体类
生成器模式|生成器模式能够使我们分步骤创建复杂的对象，使用相同的创建代码生成不同类型和形式的对象
原型模式|原型模式能够复制已有对象，而又无需使代码依赖它们所属的类。
单例模式|单例模式能够保证一个类只有一个实例，并提供一个访问该实例的全局节点

----
## 结构型模式
结构型模式（Structural Pattern）描述如何将类或者对象结合在一起形成更大的结构，就像搭积木，可以通过 简单积木的组合形成复杂的、功能更为强大的结构。结构型模式可以分为类结构型模式和对象结构型模式：
●  类结构型模式：关心类的组合，由多个类可以组合成一个更大的系统，在类结构型模式中一般只存在继承关系和实现关系 
●  对象结构型模式：关心类与对象的组合，通过关联关系使得在一 个类中定义另一个类的实例对象，然后通过该对象调用其方法 

模式名称|总结
-------|-----
适配器模式|让接口不兼容的对象能够相互合作
桥模式|可将一个大类或一系列紧密相关的类拆分为抽象和实现两个独立的层次结构，从而能在开发时分别使用
组合模式|你可以使用它将对象组合成树状结构，并且能像使用独立对象一样使用它们
装饰器模式|允许你将对象放入包含行为的特殊封装对象中来为原对象绑定新的行为
门面模式（外观模式）|能为程序库、框架或其他复杂类提供一个简单的接口
享元模式|摒弃了再每个对象中保存所有数据的方式，通过共享多个对象所共有的相同状态，让你能在优先的内存容量中载入更多对象
代理模式|让你能够提供对象的替代品或其占位符。代理控制着对于原对象的访问，并允许在将请求提交给对象前后进行一些处理

----
## 行为型模式
行为型模式（Behavioral Pattern）是对在不同的对象之间划分责任和算法的抽象化。行为型模式不仅仅关注类和对象的结构，而且重点关注它们之间的相互作用。通过行为型模式，可以更加清晰地划分类与对象的职责，并研究系统在运行时实例对象 之间的交互。在系统运行时，对象并不是孤立的，它们可以通过相互通信与协作完成某些复杂功能，一个对象在运行时也将影响到其他对象的运行。行为型模式分为类行为型模式和对象行为型模式两种：
● 类行为型模式：类的行为型模式使用继承关系在几个类之间分配行为，类行为型模式主要通过多态等方式来分配父类与子类的职责。
● 对象行为型模式：对象的行为型模式则使用对象的聚合关联关系来分配行为，对象行为型模式主要是通过对象关联等方式来分配两个或多个类的职责。

模式名称|总结
-------|-----
责任链模式|允许你讲请求沿着处理者链进行发送。收到请求后，每个处理者可对请求进行处理，或将其传递给链上的下个处理者。
命令模式|它可将请求转换为一个包含与请求相关的所有信息的独立对象。该转换让你能根据不同的请求将方法参数化、延迟请求执行或将其放入队列中，且能实现可撤销操作。
备忘录模式|允许在不暴露对象实现细节的情况下保存和恢复对象之前的状态。
策略模式|能让你定义一系列算法，并将每种算法分别放入独立的类中，以使算法的对象能够相互替换。
模板方法|在超类中定义一个算法的框架，允许子类在不修改结构的情况下重写算法的特定步骤。
迭代器模式|让你能在不暴露集合底层表现形式（列表、栈和树等）的情况下遍历集合中所有的元素。
中介者模式|能让你减少对象之间混乱无序的依赖关系。该模式会限制对象之间的直接交互，迫使它们通过一个中介者对象进行合作。
访问者模式|将算法与其所作用的对象隔离开来。
观察者模式|允许你定义一种订阅机制，可在对象事件发生时通知多个“观察”该对象的其他对象。
状态模式|让你能在一个对象的内部状态变化时改变其行为，使其看上去就像改变了自身所属的类一样。

-----
## 各个模式的主要特点
### 工厂模式
工厂方法模式建议使用特殊的工厂方法代替对于对象构造函数的直接调用（即使用 new 运算符）。不用担心，对象仍将通过 new 运算符创建，只是该运算符改在工厂方法中调用罢了。工厂方法返回的对象通常被称作“产品”。

### 抽象工厂模式
抽象工厂为你提供了一个接口，可用于创建每个系列产品的对象。只要代码通过该接口创建对象，那么你就不会生成与应用程序已生成的产品类型不一致的产品。

### 生成器模式
生成器模式建议将对象构造代码从产品类中抽取出来，并将其放在一个名为生成器的独立对象中。重点在于你无需调用所有步骤，而只需调用创建特定对象配置所需的那些步骤即可。

### 原型模式
针对复制问题，如果你有一个对象，并希望生成与其完全相同的一个复制品，就采用原型模式，总的来说，支持对象克隆的就是原型。对于循环引用的对象，克隆可能会非常麻烦

### 单例模式
为什么会有人想要控制一个类所拥有的实例数量？最常见的原因是控制某些共享资源（例如数据库或文件）的访问权限。它的运作方式是这样的：如果你创建了一个对象，同时过一会儿后你决定再创建一个新对象，此时你会获得之前已创建的对象，而不是一个新对象。主要有两种实现方式：懒汉式和饿汉式，由创建实例的时间区分。其中比较推荐的懒汉单例是创建函数返回局部的静态变量的引用。

### 适配器模式
当两个类的接口发生冲突时，可以新建一个适配器类，实现两个类直接的中介。创建一个适配器——一个特殊的对象，能够转换对象接口，使其能与其他对象进行交互。例如json文件和xml文件接口不一致时可以实现两个文件之间的转化。适配器通常在已有的程序中使用。

### 桥模式
如果你想要拆分或重组一个具有多重功能的庞杂类（例如能与多个数据库服务器进行交互的类），可以使用桥接模式。如果你希望在几个独立维度上扩展一个类，可使用该模式。如果你需要在运行时切换不同实现方法，可使用桥接模式。

### 组合模式
别名又叫对象树，采用组合模式可以使对象像树状结构一样组合，也可以像独立对象一样使用。组合模式提供了两种共享公共接口的基本元素类型：简单叶节点和复杂容器。容器中可以包含叶节点和其他容器。这使得可以构建树状嵌套递归对象结构。当然这建立在功能差异较小的类的前提下。桥接、状态和策略实际上都是基于组合模式


### 装饰器模式
就相当于给原来的类添加了装饰。如果你希望在无需修改代码的情况下即可使用对象，且希望在运行时为对象新增额外的行为，可以使用装饰模式。如果用继承来扩展对象行为的方案难以实现或者根本不可行，你可以使用该模式。适配器能为被封装对象提供不同的接口，代理能为对象提供相同的接口，装饰则能为对象提供加强的接口。适配器可以对已有对象的接口进行修改，装饰则能在不改变对象接口的前提下强化对象功能。

### 门面模式
简单来说就是为一些列的子系统的复杂操作添加了一个简单的接口。

### 享元模式
比如大量相同的对象，游戏中的子弹、粒子特效等。这些对象仅有一些部分不相同，大部分的都是不用改变的内在，但是这部分占了很大的内存空间。所以为了对象的复用，将需要占据大空间的变量移动到很少的享元对象中，让其被其他对象复用，而不是拷贝在内存中。所以不可变的成员才会存储在享元对象中。仅在程序必须支持大量对象且没有足够的内存容量时使用享元模式。

### 代理模式
代理模式就是提供一个对象的抽象，在需要延迟初始化或者只希望特定客户端使用服务对象或者本地执行远程服务。适配器能为被封装对象提供不同的接口，代理能为对象提供相同的接口，装饰则能为对象提供加强的接口。

### 责任链模式
模式建议你将这些处理者连成一条链。链上的每个处理者都有一个成员变量来保存对于下一处理者的引用。除了处理请求外，处理者还负责沿着链传递请求。请求会在链上移动，直至所有处理者都有机会对其进行处理。最重要的是：处理者可以决定不再沿着链传递请求，这可高效地取消所有后续处理步骤。所有处理者类均实现同一接口是关键所在。当程序需要使用不同方式处理不同种类请求，而且请求类型和顺序预先未知时，可以使用责任链模式。当必须按顺序执行多个处理者时，可以使用该模式。


### 命令模式
命令模式建议将请求的所有细节（例如调用的对象、方法名称和参数列表）抽取出来组成命令类，该类中仅包含一个触发请求的方法。命令对象负责连接不同的 GUI 和业务逻辑对象。让所有命令实现相同的接口。该接口通常只有一个没有任何参数的执行方法，让你能在不和具体命令类耦合的情况下使用同一请求发送者执行不同命令。如果你需要通过操作来参数化对象，可使用命令模式。如果你想要将操作放入队列中、操作的执行或者远程执行操作，可使用命令模式。如果你想要实现操作回滚功能，可使用命令模式。

### 迭代器模式
当集合背后为复杂的数据结构，且你希望对客户端隐藏其复杂性时（出于使用便利性或安全性的考虑），可以使用迭代器模式。使用该模式可以减少程序中重复的遍历代码。如果你希望代码能够遍历不同的甚至是无法预知的数据结构，可以使用迭代器模式。
