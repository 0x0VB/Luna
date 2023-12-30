---@meta
---@class FieldData
---@class LunaStruct
---@field DataCost integer The size of this struct in bytes.
---@field Type string The name of this struct's class.
local Struct = {};
---@class LunaClass
---@field DataCost integer The size of this class in bytes.
---@field Type string The name of this instance's class.
local Class = {};
---@class LunaGameObject: table
---@alias LunaProxy LunaStruct | LunaClass | LunaGameObject

---Copies the memory that this class occupies into a new address and returns the result.
function Class:Copy() return self; end;

---Copies the memory that this class occupies into a new address and returns the result.
function Class:Clone() return self; end;

---Copies the memory that this structure occupies into a new address and returns the result.
function Struct:Copy() return self; end;

---Copies the memory that this structure occupies into a new address and returns the result.
function Struct:Clone() return self; end;

--LunaClass library V 4.0. Can be used to create custom classes.<br>
--<b><u>[CORE]</u> this is a core library. Use it with caution.</b>
LunaClass = {
    --Memory manipulation library used to interpret memory as certain lua types or write to memory.<br>
    --<b><u>[CORE]</u> this is a core library. Use it with caution.</b>
    TypeCasts = {
        ---Reads the memory at the given `Address` as a single character value and returns the value. If `Value` is provided, 
        ---it writes it to the given `Address` instead.
        ---@param Address integer
        ---@param Value string?
        ---@return string?
        Char = function(Address, Value) return ""; end;

        ---Reads the memory at the given `Address` as a boolean value and returns the value. If `Value` is provided, 
        ---it writes it to the given `Address` instead.
        ---@param Address integer
        ---@param Value boolean?
        ---@return boolean?
        Bool = function(Address, Value) return true; end;

        ---Reads the memory at the given `Address` as a single byte between 0-255 and returns the value. If `Value` is provided, 
        ---it writes it to the given `Address` instead.
        ---@param Address integer
        ---@param Value integer?
        ---@return integer?
        Byte = function(Address, Value) return 0; end;

        ---Reads the memory at the given `Address` as a word between 0-255^2 and returns the value. If `Value` is provided, 
        ---it writes it to the given `Address` instead.
        ---@param Address integer
        ---@param Value integer?
        ---@return integer?
        Word = function(Address, Value) return 0; end;

        ---Reads the memory at the given `Address` as an integer and returns the value. If `Value` is provided, 
        ---it writes it to the given `Address` instead.
        ---@param Address integer
        ---@param Value integer?
        ---@return integer?
        Int = function(Address, Value) return 0; end;

        ---Reads the memory at the given `Address` as a long value and returns the value. If `Value` is provided, 
        ---it writes it to the given `Address` instead.
        ---@param Address integer
        ---@param Value number?
        ---@return number?
        Long = function(Address, Value) return 0; end;

        ---Reads the memory at the given `Address` as a floating point value and returns the value. If `Value` is provided, 
        ---it writes it to the given `Address` instead.
        ---@param Address integer
        ---@param Value number?
        ---@return number?
        Float = function(Address, Value) return 0; end;

        ---Reads the memory at the given `Address` as a double value and returns the value. If `Value` is provided, 
        ---it writes it to the given `Address` instead.
        ---@param Address integer
        ---@param Value number?
        ---@return number?
        Double = function(Address, Value) return 0; end;

        ---Reads the memory at the given `Address` as a string and returns the value. If `Value` is provided, 
        ---it writes it to the given `Address` instead.
        ---@param Address integer
        ---@param Value string?
        ---@return string?
        String = function(Address, Value) return ""; end;

        ---Reads the memory at the given `Address` as an integer Vector2 and returns the value. If `Value` is provided, 
        ---it writes it to the given `Address` instead.
        ---@param Address integer
        ---@param Value Vector2?
        ---@return IVector2?
        IVector2 = function(Address, Value) return; end;

        ---Reads the memory at the given `Address` as a floating point Vector2 and returns the value. If `Value` is provided, 
        ---it writes it to the given `Address` instead.
        ---@param Address integer
        ---@param Value Vector2?
        ---@return FVector2?
        FVector2 = function(Address, Value) return; end;

        ---Reads the memory at the given `Address` as Rect and returns the value. If `Value` is provided, 
        ---it writes it to the given `Address` instead.
        ---@param Address integer
        ---@param Value Rect?
        ---@return Rect?
        RVector4 = function(Address, Value) return; end;

        ---Reads the memory at the given `Address` as Pad and returns the value. If `Value` is provided, 
        ---it writes it to the given `Address` instead.
        ---@param Address integer
        ---@param Value Pad?
        ---@return Pad?
        PVector4 = function(Address, Value) return; end;

        ---Reads the memory at the given `Address` as Pad and returns the value. If `Value` is provided, 
        ---it writes it to the given `Address` instead.
        ---@param Address integer
        ---@param Value Vector3?
        ---@return Vector3?
        FVector3 = function (Address, Value) return; end;

        ---Gets an array of bytes at the given address with the given length.
        ---@param Address integer
        ---@param Length integer
        ---@return string
        ---@nodiscard
        ---@overload fun(Address, Value): nil Writes the given string to the given address as an array of bytes.
        AOB = function(Address, Length) return ""; end;

        ---Gets a character array at the given address that ends when it finds a NULL terminator.
        ---@param Address integer
        ---@return string
        ---@nodiscard
        CArr = function(Address) return "" end;

        ---Copies `DataCost` number of bytes from `Source` onto `Destination`.
        ---@param Destination integer
        ---@param Source integer
        ---@param DataCost integer
        MemAOB = function(Destination, Source, DataCost) end;

        ---Attempts to guess the type of the UIElement at the given address via its VFTable pointer.
        ---@param Address integer
        ---@return UIContainer
        UI = function(Address) return ({})[0]; end;
    };

    ---Creates a new FieldData instance with the given parameters.
    ---@param Offset integer The offset of this field from the base address of the class.
    ---@param IsPointer boolean Whether this field is a pointer to a value or not.
    ---@param IsClass boolean Whether this field is an embedded sub-class in this clss or not.
    ---@param Data function | string If the field is a class, a ClassName is expected for this parameter. 
    ---Otherwise, the TypeCast function is supplied.
    ---@return FieldData
    ---@nodiscard
    NewField = function(Offset, IsPointer, IsClass, Data) return ({})[0]; end;

    ---Registers a new class with the given parameters and returns the template after inheritance has been performed.
    ---@param ClassName string The name of the class.
    ---@param Template table The class template. Contains static fields or FieldData values that describe the field.
    ---@param DataCost integer The size of the class in memory in bytes.
    ---@param SupportDynamicFields boolean? Accepts fields not registered in the class as custom fields.
    ---@param InheritedClass string? The ClassName of the class that this class inherits, if it inherits anything.
    ---@return table
    Register = function(ClassName, Template, DataCost, SupportDynamicFields, InheritedClass) return {}; end;

    ---Creates and returns an instance of the given class. 
    ---Make sure to cast the returns of this function to the desired type in order for the autocomplete to work.
    ---@param ClassName string The name of the desired class.
    ---@param Address integer The base address of the class in memory.
    ---@param Flush boolean? Whether or not to flush the class upon creation. Flushing the class clears all of its DynamicFields.
    ---@return LunaClass
    ---@nodiscard
    Create = function(ClassName, Address, Flush) return ({})[0]; end;

    ---Clears all of the given instance's DynamicFields.
    ---@param self LunaClass
    Flush = function(self) end;
};

---Returns the DataCost of the given class.
---@param self LunaProxy
---@return integer
function DataCost(self) return 0; end;