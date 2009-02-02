s/static VALUE mCore;/VALUE mCore;/
s/mCore = rb_define_module("Core")/mFox = rb_define_module("Fox")/
s/mCore/mFox/
/static VALUE mDc;/d
/mDc = rb_define_module/d
/static VALUE mDialogs;/d
/mDialogs = rb_define_module/d
/static VALUE mFrames;/d
/mFrames = rb_define_module/d
/static VALUE mIconlist;/d
/mIconlist = rb_define_module/d
/static VALUE mIcons;/d
/mIcons = rb_define_module/d
/static VALUE mImage;/d
/mImage = rb_define_module/d
/static VALUE mLabel;/d
/mLabel = rb_define_module/d
/static VALUE mLayout;/d
/mLayout = rb_define_module/d
/static VALUE mList;/d
/mList = rb_define_module/d
/static VALUE mMdi;/d
/mMdi = rb_define_module/d
/static VALUE mMenu;/d
/mMenu = rb_define_module/d
/static VALUE mFx3d;/d
/mFx3d = rb_define_module/d
/static VALUE mScintilla;/d
/mScintilla = rb_define_module/d
/static VALUE mTable;/d
/mTable = rb_define_module/d
/static VALUE mText;/d
/mText = rb_define_module/d
/static VALUE mTreelist;/d
/mTreelist = rb_define_module/d
/static VALUE mUi;/d
/mUi = rb_define_module/d
/rb_require/d
s/mDc,/mFox,/
s/mDialogs,/mFox,/
s/mFrames,/mFox,/
s/mIconlist,/mFox,/
s/mIcons,/mFox,/
s/mImage,/mFox,/
s/mLabel,/mFox,/
s/mLayout,/mFox,/
s/mList,/mFox,/
s/mMdi,/mFox,/
s/mMenu,/mFox,/
s/mFx3d,/mFox,/
s/mScintilla,/mFox,/
s/mTable,/mFox,/
s/mText,/mFox,/
s/mTreelist,/mFox,/
s/mUi,/mFox,/
