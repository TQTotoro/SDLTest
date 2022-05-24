window和renderer由一个类管理
texture由一个类管理，只负责加载资源，具体绘制什么内容不决定，留出接口即可
object：自己决定参数是什么，然后调用texture留出的接口

状态机：
	pushState之后，onEnter()
	popState之前，onExit()