/*
 * ========================= ActionSwitch.h ==========================
 *                          -- tpr --
 *                                        CREATE -- 2019.02.01
 *                                        MODIFY -- 
 * ----------------------------------------------------------
 *    
 * ----------------------------
 */
#ifndef _TPR_ACTION_SWITCH_H_
#define _TPR_ACTION_SWITCH_H_

//-------------------- CPP --------------------//
#include <functional>

//------------------- Libs --------------------//
#include "tprDataType.h" 

//-------------------- Engine --------------------//
#include "ActionSwitchType.h"



//--- need ---//
class GameObj;


class ActionSwitch{
public:
    using F_ACTION_SWITCH = std::function<void(GameObj*, ActionSwitchType)>;

    ActionSwitch() = default;

    inline void init( GameObj *_goPtr ){
        goPtr = _goPtr;
    }



    inline void call_func( ActionSwitchType _type ){

        if( func == nullptr ){
            return;
        }

        //-- 如果本实例 没装载此 _type，也将安全返回 --
        if( check(_type) == false ){
            return;
        }

        //-- 正式call --
        func( goPtr, _type );
    }


    inline void clear_typeMap(){
        typeMap = 0;
    }

    //-- 登记某个 actionSwitch --
    inline void sign_up( ActionSwitchType _type ){
        typeMap = typeMap | (1 << (int)_type);
    }

    //-- 检查某个 actionSwitch 是否已登记 --
    inline bool check( ActionSwitchType _type ){
        return  ( ((typeMap>>((int)_type)) & 1)==1 );
    }
    

    //--- functor ----//
    //  最好放到 private 中去
    F_ACTION_SWITCH  func {nullptr};


private:
    GameObj *goPtr {nullptr};

    u64  typeMap {0}; //- 位图，记录了本实例 注册了哪几个类型的 actionSwitch
                      //- 暂定上限为 64 个
    
};





#endif 
